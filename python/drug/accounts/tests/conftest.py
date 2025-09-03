import pytest
from django.core.management import call_command

@pytest.fixture(scope='session')
def django_db_setup(django_db_setup, django_db_blocker):
    """Настройка тестовой БД"""
    with django_db_blocker.unblock():
        pass

@pytest.fixture(autouse=True)
def enable_db_access_for_all_tests(db):
    """Автоматический доступ к БД для всех тестов"""
    pass

@pytest.fixture
def no_db_access():
    """Фикстура для тестов без доступа к БД"""
    pass

@pytest.fixture
def api_client():
    """API клиент для тестов"""
    from rest_framework.test import APIClient
    return APIClient()

@pytest.fixture
def user():
    """Обычный пользователь"""
    from .factories import UserFactory
    return UserFactory()

@pytest.fixture
def user_with_profile():
    """Пользователь с заполненным профилем"""
    from .factories import UserWithProfileFactory
    return UserWithProfileFactory()

@pytest.fixture
def veterinarian():
    """Пользователь-ветеринар"""
    from .factories import VeterinarianUserFactory
    return VeterinarianUserFactory()

@pytest.fixture
def admin_user():
    """Администратор"""
    from .factories import AdminUserFactory
    return AdminUserFactory()

@pytest.fixture
def authenticated_client(api_client, user):
    """API клиент с авторизованным пользователем"""
    from rest_framework.authtoken.models import Token
    token, _ = Token.objects.get_or_create(user=user)
    api_client.credentials(HTTP_AUTHORIZATION=f'Token {token.key}')
    api_client.user = user
    return api_client

@pytest.fixture
def admin_client(api_client, admin_user):
    """API клиент с администратором"""
    from rest_framework.authtoken.models import Token
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
    from .factories import UserFactory, VeterinarianUserFactory, AdminUserFactory
    return {
        'pet_owner': UserFactory(user_type='pet_owner'),
        'veterinarian': VeterinarianUserFactory(),
        'business': UserFactory(user_type='business'),
        'admin': AdminUserFactory()
    }