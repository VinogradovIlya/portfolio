import os
import django
from django.conf import settings

def pytest_configure():
    """Конфигурация Django для pytest"""
    os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'config.settings.testing')
    django.setup()