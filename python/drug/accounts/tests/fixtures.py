import pytest
from rest_framework.test import APIClient
from rest_framework.authtoken.models import Token
from django.contrib.auth import get_user_model
from .factories import (
    UserFactory, 
    UserWithProfileFactory,
    VeterinarianUserFactory,
    AdminUserFactory,
)

User = get_user_model()


@pytest.fixture
def api_client():
    """API клиент для тестов"""
    return APIClient()


@pytest.fixture
def user():
    """Обычный пользователь"""
    return UserFactory()


@pytest.fixture
def user_with_profile():
    """Пользователь с заполненным профилем"""
    return UserWithProfileFactory()


@pytest.fixture
def veterinarian():
    """Пользователь-ветеринар"""
    return VeterinarianUserFactory()


@pytest.fixture
def admin_user():
    """Администратор"""
    return AdminUserFactory()


@pytest.fixture  
def authenticated_client(api_client, user):
    """API клиент с авторизованным пользователем"""
    token, _ = Token.objects.get_or_create(user=user)
    api_client.credentials(HTTP_AUTHORIZATION=f'Token {token.key}')
    api_client.user = user  # Сохраняем ссылку на пользователя
    return api_client


@pytest.fixture
def admin_client(api_client, admin_user):
    """API клиент с администратором"""
    token, _ = Token.objects.get_or_create(user=admin_user)
    api_client.credentials(HTTP_AUTHORIZATION=f'Token {token.key}')
    api_client.user = admin_user
    return api_client


@pytest.fixture
def registration_data():
    """Данные для регистрации"""
    return {
        'email': 'test@example.com',
        'password': 'testpassword123',
        'password_confirm': 'testpassword123',
        'user_type': 'pet_owner',
        'phone': '+79151234567',
        'city': 'Moscow'
    }


@pytest.fixture
def login_data():
    """Данные для входа"""
    return {
        'email': 'test@example.com',
        'password': 'testpassword123'
    }


@pytest.fixture
def profile_data():
    """Данные профиля"""
    return {
        'first_name': 'Иван',
        'last_name': 'Петров',
        'middle_name': 'Сергеевич',
        'gender': 'm',
        'bio': 'Люблю своих питомцев'
    }


@pytest.fixture
def multiple_users():
    """Несколько пользователей разных типов"""
    return {
        'pet_owner': UserFactory(user_type='pet_owner'),
        'veterinarian': VeterinarianUserFactory(),
        'business': UserFactory(user_type='business'),
        'admin': AdminUserFactory()
    }