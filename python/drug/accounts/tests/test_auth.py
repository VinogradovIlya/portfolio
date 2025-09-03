import pytest
from django.contrib.auth import get_user_model, authenticate
from rest_framework.authtoken.models import Token
from .factories import UserFactory, InactiveUserFactory

User = get_user_model()

pytestmark = pytest.mark.django_db


class TestCustomUserManager:
    """Тесты кастомного менеджера пользователей"""
    
    def test_create_user(self):
        """Тест создания обычного пользователя"""
        user = User.objects.create_user(
            email='test@example.com',
            password='testpass123',
            user_type='pet_owner',
            phone='+79151234567',
            city='Moscow'
        )
        
        assert user.email == 'test@example.com'
        assert user.check_password('testpass123')
        assert user.user_type == 'pet_owner'
        assert not user.is_staff
        assert not user.is_superuser
        assert user.is_active
    
    def test_create_user_without_email(self):
        """Тест создания пользователя без email"""
        with pytest.raises(ValueError, match='Email is required'):
            User.objects.create_user(
                email='',
                password='testpass123'
            )
    
    def test_create_superuser(self):
        """Тест создания суперпользователя"""
        admin = User.objects.create_superuser(
            email='admin@example.com',
            password='adminpass123'
        )
        
        assert admin.email == 'admin@example.com'
        assert admin.check_password('adminpass123')
        assert admin.user_type == 'admin'
        assert admin.is_staff
        assert admin.is_superuser
        assert admin.is_active


class TestAuthentication:
    """Тесты системы аутентификации"""
    
    def test_authenticate_valid_user(self):
        """Тест аутентификации существующего пользователя"""
        user = UserFactory(
            email='valid@example.com',
            password='validpass123'
        )
        
        authenticated_user = authenticate(
            email='valid@example.com',
            password='validpass123'
        )
        
        assert authenticated_user == user
        assert authenticated_user.is_authenticated
    
    def test_authenticate_invalid_password(self):
        """Тест аутентификации с неверным паролем"""
        UserFactory(
            email='test@example.com',
            password='correctpass'
        )
        
        authenticated_user = authenticate(
            email='test@example.com',
            password='wrongpass'
        )
        
        assert authenticated_user is None
    
    def test_authenticate_nonexistent_user(self):
        """Тест аутентификации несуществующего пользователя"""
        authenticated_user = authenticate(
            email='nonexistent@example.com',
            password='somepass'
        )
        
        assert authenticated_user is None
    
    def test_authenticate_inactive_user(self):
        """Тест аутентификации заблокированного пользователя"""
        inactive_user = InactiveUserFactory(
            email='inactive@example.com',
            password='testpass123'
        )
        
        authenticated_user = authenticate(
            email='inactive@example.com',
            password='testpass123'
        )
        
        # Django по умолчанию не аутентифицирует неактивных пользователей
        assert authenticated_user is None


class TestTokenAuthentication:
    """Тесты токен-аутентификации"""
    
    def test_token_creation(self):
        """Тест создания токена для пользователя"""
        user = UserFactory()
        
        token, created = Token.objects.get_or_create(user=user)
        
        assert created is True
        assert token.user == user
        assert len(token.key) == 40
    
    def test_token_uniqueness(self):
        """Тест уникальности токенов"""
        user1 = UserFactory()
        user2 = UserFactory()
        
        token1 = Token.objects.create(user=user1)
        token2 = Token.objects.create(user=user2)
        
        assert token1.key != token2.key
    
    def test_token_deletion_on_user_delete(self):
        """Тест удаления токена при удалении пользователя"""
        user = UserFactory()
        token = Token.objects.create(user=user)
        token_key = token.key
        
        user.delete()
        
        assert not Token.objects.filter(key=token_key).exists()
    
    def test_multiple_tokens_not_allowed(self):
        """Тест что у пользователя может быть только один токен"""
        user = UserFactory()
        
        token1 = Token.objects.create(user=user)
        token2, created = Token.objects.get_or_create(user=user)
        
        assert not created
        assert token1 == token2
        assert Token.objects.filter(user=user).count() == 1


class TestPasswordSecurity:
    """Тесты безопасности паролей"""
    
    def test_password_hashing(self):
        """Тест хеширования паролей"""
        user = UserFactory(password='plaintext_password')
        
        assert user.password != 'plaintext_password'
        assert user.password.startswith('pbkdf2_sha256')
        
        assert user.check_password('plaintext_password')
        assert not user.check_password('wrong_password')
    
    def test_password_change(self):
        """Тест смены пароля"""
        user = UserFactory(password='old_password')
        
        assert user.check_password('old_password')
        
        user.set_password('new_password')
        user.save()
        
        assert not user.check_password('old_password')
        assert user.check_password('new_password')
    
    def test_empty_password_handling(self):
        """Тест обработки пустых паролей"""
        user = UserFactory()
        user.set_password('')
        
        assert not user.check_password('')
        assert not user.check_password('any_password')

