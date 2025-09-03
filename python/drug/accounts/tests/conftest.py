import pytest
from django.core.management import call_command


@pytest.fixture(scope='session')
def django_db_setup(django_db_setup, django_db_blocker):
    """Настройка тестовой БД"""
    with django_db_blocker.unblock():
        # Создаем необходимые данные для всех тестов
        call_command('loaddata', 'test_fixtures.json', verbosity=0)


@pytest.fixture(autouse=True)
def enable_db_access_for_all_tests(db):
    """Автоматический доступ к БД для всех тестов"""
    pass


@pytest.fixture
def no_db_access():
    """Фикстура для тестов без доступа к БД"""
    pass