import pytest
from rest_framework import status
from rest_framework.authtoken.models import Token
from django.contrib.auth import get_user_model
# from django.urls import reverse
from .factories import UserFactory, UserWithProfileFactory

User = get_user_model()

pytestmark = pytest.mark.django_db


class TestRegistrationAPI:
    """Тесты API регистрации"""
    
    def test_registration_success(self, api_client, registration_data):
        """Тест успешной регистрации"""
        response = api_client.post('/api/auth/register/', registration_data)
        
        assert response.status_code == status.HTTP_201_CREATED
        assert 'token' in response.data
        assert 'user' in response.data
        assert response.data['user']['email'] == registration_data['email']
        
        user = User.objects.get(email=registration_data['email'])
        assert user.user_type == 'pet_owner'
        assert user.check_password('testpassword123')
    
    def test_registration_password_mismatch(self, api_client, registration_data):
        """Тест с несовпадающими паролями"""
        registration_data['password_confirm'] = 'different_password'
        
        response = api_client.post('/api/auth/register/', registration_data)
        
        assert response.status_code == status.HTTP_400_BAD_REQUEST
        assert 'password_confirm' in response.data
    
    def test_registration_duplicate_email(self, api_client, registration_data):
        """Тест дублирования email"""
        UserFactory(email=registration_data['email'])
        
        response = api_client.post('/api/auth/register/', registration_data)
        
        assert response.status_code == status.HTTP_400_BAD_REQUEST
        assert 'email' in response.data
    
    def test_registration_invalid_phone(self, api_client, registration_data):
        """Тест с некорректным телефоном"""
        registration_data['phone'] = 'invalid_phone'
        
        response = api_client.post('/api/auth/register/', registration_data)
        
        assert response.status_code == status.HTTP_400_BAD_REQUEST
        assert 'phone' in response.data
    
    def test_registration_missing_fields(self, api_client):
        """Тест с отсутствующими обязательными полями"""
        incomplete_data = {
            'email': 'test@example.com',
        }
        
        response = api_client.post('/api/auth/register/', incomplete_data)
        
        assert response.status_code == status.HTTP_400_BAD_REQUEST
        assert 'password' in response.data
        assert 'user_type' in response.data


class TestLoginAPI:
    """Тесты API авторизации"""
    
    def test_login_success(self, api_client):
        """Тест успешной авторизации"""
        user = UserFactory(
            email='test@example.com',
            password='testpassword123'
        )
        
        login_data = {
            'email': 'test@example.com',
            'password': 'testpassword123'
        }
        
        response = api_client.post('/api/auth/login/', login_data)
        
        assert response.status_code == status.HTTP_200_OK
        assert 'token' in response.data
        assert 'user' in response.data
        assert response.data['user']['id'] == user.id
        
        assert Token.objects.filter(user=user).exists()
    
    def test_login_invalid_credentials(self, api_client):
        """Тест с неверными данными"""
        UserFactory(email='test@example.com', password='correct_password')
        
        login_data = {
            'email': 'test@example.com', 
            'password': 'wrong_password'
        }
        
        response = api_client.post('/api/auth/login/', login_data)
        
        assert response.status_code == status.HTTP_400_BAD_REQUEST
    
    def test_login_nonexistent_user(self, api_client):
        """Тест входа несуществующего пользователя"""
        login_data = {
            'email': 'nonexistent@example.com',
            'password': 'somepassword'
        }
        
        response = api_client.post('/api/auth/login/', login_data)
        
        assert response.status_code == status.HTTP_400_BAD_REQUEST
    
    def test_login_inactive_user(self, api_client):
        """Тест входа заблокированного пользователя"""
        UserFactory(
            email='blocked@example.com',
            password='testpass123',
            is_active=False
        )
        
        login_data = {
            'email': 'blocked@example.com',
            'password': 'testpass123'
        }
        
        response = api_client.post('/api/auth/login/', login_data)
        
        assert response.status_code == status.HTTP_400_BAD_REQUEST


class TestProfileAPI:
    """Тесты API профиля"""
    
    def test_get_profile_authenticated(self, authenticated_client):
        """Тест получения профиля авторизованным пользователем"""
        response = authenticated_client.get('/api/auth/profile/')
        
        assert response.status_code == status.HTTP_200_OK
        assert 'email' in response.data
        assert response.data['id'] == authenticated_client.user.id
    
    def test_get_profile_unauthenticated(self, api_client):
        """Тест получения профиля без авторизации"""
        response = api_client.get('/api/auth/profile/')
        
        assert response.status_code == status.HTTP_401_UNAUTHORIZED
    
    def test_profile_with_user_profile_data(self, api_client):
        """Тест профиля пользователя с заполненными личными данными"""
        user_with_profile = UserWithProfileFactory()
        token = Token.objects.create(user=user_with_profile)
        
        api_client.credentials(HTTP_AUTHORIZATION=f'Token {token.key}')
        response = api_client.get('/api/auth/profile/')
        
        assert response.status_code == status.HTTP_200_OK
        assert 'profile' in response.data
        assert response.data['profile']['first_name'] == user_with_profile.profile.first_name


class TestLogoutAPI:
    """Тесты API выхода"""
    
    def test_logout_success(self, authenticated_client):
        """Тест успешного выхода"""
        user = authenticated_client.user
        
        assert Token.objects.filter(user=user).exists()
        
        response = authenticated_client.post('/api/auth/logout/')
        
        assert response.status_code == status.HTTP_200_OK
        assert 'message' in response.data
        
        assert not Token.objects.filter(user=user).exists()
    
    def test_logout_unauthenticated(self, api_client):
        """Тест выхода без авторизации"""
        response = api_client.post('/api/auth/logout/')
        
        assert response.status_code == status.HTTP_401_UNAUTHORIZED


class TestPermissions:
    """Тесты прав доступа"""
    
    def test_different_user_types_access(self, api_client, multiple_users):
        """Тест доступа разных типов пользователей"""
        for user_type, user in multiple_users.items():
            token = Token.objects.create(user=user)
            api_client.credentials(HTTP_AUTHORIZATION=f'Token {token.key}')
            
            response = api_client.get('/api/auth/profile/')
            
            assert response.status_code == status.HTTP_200_OK
            assert response.data['user_type'] == user_type
            
            api_client.credentials()