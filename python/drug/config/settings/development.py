"""
Development settings for drug_backend project.
"""

from .base import *

DEBUG = True

ALLOWED_HOSTS = [
    'localhost',
    '127.0.0.1',
    '0.0.0.0',
    '.ngrok.io',  # для тестирования с мобильных устройств
]

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',
        'NAME': os.environ.get('DB_NAME', 'drug_database'),
        'USER': os.environ.get('DB_USER', 'willames'),
        'PASSWORD': os.environ.get('DB_PASSWORD', 'password'),
        'HOST': os.environ.get('DB_HOST', 'localhost'),
        'PORT': os.environ.get('DB_PORT', '5432'),
    }
}

# Email backend для разработки
# EMAIL_BACKEND = 'django.core.mail.backends.console.EmailBackend'

# Cache для разработки
CACHES = {
    'default': {
        'BACKEND': 'django.core.cache.backends.locmem.LocMemCache',
        'LOCATION': 'unique-snowflake',
    }
}
# Дополнительные приложения для разработки
INSTALLED_APPS += [
    # 'debug_toolbar',
    # 'django_extensions',
]

# MIDDLEWARE += [
#     'debug_toolbar.middleware.DebugToolbarMiddleware',
# ]

# Debug Toolbar настройки
INTERNAL_IPS = [
    '127.0.0.1',
    'localhost',
]

# Менее строгие настройки CORS для разработки
CORS_ALLOW_ALL_ORIGINS = True
CORS_ALLOW_CREDENTIALS = True

# Логирование для разработки (более подробное)
LOGGING['root']['level'] = 'DEBUG'
LOGGING['loggers']['django']['level'] = 'DEBUG'