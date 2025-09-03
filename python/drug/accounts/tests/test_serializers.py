import pytest
from django.contrib.auth import get_user_model
from accounts.serializers import (
    UserRegistrationSerializer,
    UserLoginSerializer,
    UserSerializer,
    UserProfileSerializer
)
from .factories import UserFactory, UserProfileFactory, UserWithProfileFactory

User = get_user_model()

pytestmark = pytest.mark.django_db


class TestUserRegistrationSerializer:
    """Тесты сериализатора регистрации"""
    
    def test_valid_registration_data(self, registration_data):
        """Тест валидации корректных данных"""
        serializer = UserRegistrationSerializer(data=registration_data)
        
        assert serializer.is_valid()
        assert serializer.validated_data['email'] == registration_data['email']
    
    def test_password_mismatch(self, registration_data):
        """Тест несовпадения паролей"""
        registration_data['password_confirm'] = 'different_password'
        
        serializer = UserRegistrationSerializer(data=registration_data)
        
        assert not serializer.is_valid()
        assert 'password_confirm' in serializer.errors
    
    def test_create_user(self, registration_data):
        """Тест создания пользователя через сериализатор"""
        serializer = UserRegistrationSerializer(data=registration_data)
        
        assert serializer.is_valid()
        user = serializer.save()
        
        assert user.email == registration_data['email']
        assert user.check_password(registration_data['password'])
        assert user.user_type == registration_data['user_type']
    
    def test_password_validation(self, registration_data):
        """Тест валидации пароля"""
        registration_data['password'] = '123'
        registration_data['password_confirm'] = '123'
        
        serializer = UserRegistrationSerializer(data=registration_data)
        
        assert not serializer.is_valid()
        assert 'password' in serializer.errors


class TestUserLoginSerializer:
    """Тесты сериализатора авторизации"""
    
    def test_valid_login_data(self):
        """Тест валидации корректных данных входа"""
        user = UserFactory(
            email='test@example.com',
            password='testpass123'
        )
        
        login_data = {
            'email': 'test@example.com',
            'password': 'testpass123'
        }
        
        serializer = UserLoginSerializer(data=login_data)
        
        assert serializer.is_valid()
        assert serializer.validated_data['user'] == user
    
    def test_invalid_credentials(self):
        """Тест неверных данных"""
        UserFactory(email='test@example.com', password='correct_password')
        
        login_data = {
            'email': 'test@example.com',
            'password': 'wrong_password'
        }
        
        serializer = UserLoginSerializer(data=login_data)
        
        assert not serializer.is_valid()
        assert 'non_field_errors' in serializer.errors
    
    def test_inactive_user_login(self):
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
        
        serializer = UserLoginSerializer(data=login_data)
        
        assert not serializer.is_valid()


class TestUserSerializer:
    """Тесты сериализатора пользователя"""
    
    def test_user_serialization(self):
        """Тест сериализации пользователя"""
        user = UserWithProfileFactory()
        
        serializer = UserSerializer(user)
        data = serializer.data
        
        assert data['id'] == user.id
        assert data['email'] == user.email
        assert data['user_type'] == user.user_type
        assert 'profile' in data
        assert data['profile']['first_name'] == user.profile.first_name
    
    def test_user_without_profile(self):
        """Тест сериализации пользователя без профиля"""
        user = UserFactory()
        
        serializer = UserSerializer(user)
        data = serializer.data
        
        assert data['id'] == user.id
        assert data['profile'] is None
    
    def test_read_only_fields(self):
        """Тест полей только для чтения"""
        user = UserFactory()
        
        # Пытаемся изменить read_only поля
        serializer = UserSerializer(user, data={
            'id': 999,
            'is_verified': True,
            'date_joined': '2020-01-01'
        }, partial=True)
        
        assert serializer.is_valid()
        updated_user = serializer.save()
        
        assert updated_user.id == user.id
        assert updated_user.is_verified == user.is_verified
        assert updated_user.date_joined == user.date_joined


class TestUserProfileSerializer:
    """Тесты сериализатора профиля"""
    
    def test_profile_serialization(self):
        """Тест сериализации профиля"""
        profile = UserProfileFactory()
        
        serializer = UserProfileSerializer(profile)
        data = serializer.data
        
        assert data['first_name'] == profile.first_name
        assert data['last_name'] == profile.last_name
        assert data['full_name'] == profile.full_name
    
    def test_profile_update(self):
        """Тест обновления профиля"""
        profile = UserProfileFactory()
        
        update_data = {
            'first_name': 'Новое Имя',
            'bio': 'Новая биография'
        }
        
        serializer = UserProfileSerializer(profile, data=update_data, partial=True)
        
        assert serializer.is_valid()
        updated_profile = serializer.save()
        
        assert updated_profile.first_name == 'Новое Имя'
        assert updated_profile.bio == 'Новая биография'