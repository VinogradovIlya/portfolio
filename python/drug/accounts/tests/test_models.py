import pytest
# from django.core.exceptions import ValidationError
from django.db import IntegrityError
from django.contrib.auth import get_user_model
from accounts.models import UserProfile
from .factories import UserFactory, UserProfileFactory, UserWithProfileFactory

User = get_user_model()

pytestmark = pytest.mark.django_db


class TestUserModel:
    """Тесты модели User"""
    
    def test_create_user_success(self):
        """Тест успешного создания пользователя"""
        user = UserFactory()
        
        assert user.id is not None
        assert user.email
        assert user.user_type == 'pet_owner'
        assert user.is_active is True
        assert user.is_verified is False
        assert user.check_password('testpassword123')
    
    def test_email_uniqueness(self):
        """Тест уникальности email"""
        email = 'unique@example.com'
        UserFactory(email=email)
        
        with pytest.raises(IntegrityError):
            UserFactory(email=email)
    
    def test_phone_uniqueness(self):
        """Тест уникальности телефона"""
        phone = '+79151234567'
        UserFactory(phone=phone)
        
        with pytest.raises(IntegrityError):
            UserFactory(phone=phone)
    
    def test_user_str_representation(self):
        """Тест строкового представления"""
        user = UserFactory(
            email='test@example.com',
            user_type='veterinarian'
        )
        
        expected = "test@example.com (Ветеринар)"
        assert str(user) == expected
    
    def test_user_types(self):
        """Тест всех типов пользователей"""
        user_types = ['pet_owner', 'veterinarian', 'clinic_admin', 'business', 'admin']
        
        for user_type in user_types:
            user = UserFactory(user_type=user_type)
            assert user.user_type == user_type
    
    def test_custom_user_manager(self):
        """Тест кастомного менеджера пользователей"""
        user = User.objects.create_user(
            email='manager@example.com',
            password='testpass123',
            user_type='pet_owner'
        )
        
        assert user.email == 'manager@example.com'
        assert user.check_password('testpass123')
        assert not user.is_staff
        assert not user.is_superuser
    
    def test_create_superuser(self):
        """Тест создания суперпользователя"""
        admin = User.objects.create_superuser(
            email='admin@example.com',
            password='adminpass123'
        )
        
        assert admin.is_staff is True
        assert admin.is_superuser is True
        assert admin.user_type == 'admin'
    
    def test_create_user_without_email(self):
        """Тест создания пользователя без email"""
        with pytest.raises(ValueError, match='Email is required'):
            User.objects.create_user(email='', password='testpass123')


class TestUserProfileModel:
    """Тесты модели UserProfile"""
    
    def test_create_profile_success(self):
        """Тест создания профиля"""
        profile = UserProfileFactory()
        
        assert profile.id is not None
        assert profile.user.id is not None
        assert profile.first_name
        assert profile.last_name
    
    def test_profile_str_representation(self):
        """Тест строкового представления профиля"""
        profile = UserProfileFactory(
            first_name='Иван',
            last_name='Петров'
        )
        
        assert str(profile) == "Иван Петров"
    
    def test_full_name_property(self):
        """Тест свойства full_name"""
        profile = UserProfileFactory(
            first_name='Иван',
            middle_name='Сергеевич', 
            last_name='Петров'
        )
        
        assert profile.full_name == "Иван Сергеевич Петров"
    
    def test_full_name_without_middle_name(self):
        """Тест full_name без отчества"""
        profile = UserProfileFactory(
            first_name='Иван',
            middle_name='',
            last_name='Петров'
        )
        
        assert profile.full_name == "Иван Петров"
    
    def test_one_to_one_relationship(self):
        """Тест связи один-к-одному с User"""
        user = UserFactory()
        profile = UserProfileFactory(user=user)
        
        assert profile.user == user
        assert user.profile == profile
    
    def test_profile_deletion_on_user_delete(self):
        """Тест удаления профиля при удалении пользователя"""
        user_with_profile = UserWithProfileFactory()
        profile_id = user_with_profile.profile.id
        
        user_with_profile.delete()
        
        assert not UserProfile.objects.filter(id=profile_id).exists()


class TestUserProfileIntegration:
    """Интеграционные тесты User + UserProfile"""
    
    def test_user_with_profile_creation(self):
        """Тест создания пользователя с профилем"""
        user_with_profile = UserWithProfileFactory()
        
        assert user_with_profile.profile is not None
        assert user_with_profile.profile.first_name
        assert user_with_profile.profile.user == user_with_profile
    
    def test_profile_access_from_user(self):
        """Тест доступа к профилю через пользователя"""
        user = UserWithProfileFactory(
            profile__first_name='Тест',
            profile__last_name='Пользователь'
        )
        
        assert user.profile.first_name == 'Тест'
        assert user.profile.last_name == 'Пользователь'