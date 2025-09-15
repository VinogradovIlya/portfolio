"""
Django apps configuration.
"""

DJANGO_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
]

THIRD_PARTY_APPS = [
    'rest_framework',
    'rest_framework.authtoken',
    'corsheaders',
    'django_filters',
    'drf_spectacular',
    # 'celery',
    # 'django_celery_beat',
    # 'django_celery_results',
]

LOCAL_APPS = [
    'core',
    'accounts',
    'pets',
    'medical',
    'clinics',
    'marketplace',
    'notifications',
    'frontend',
    'reviews',
    'messaging',
    'bot',
]

INSTALLED_APPS = DJANGO_APPS + THIRD_PARTY_APPS + LOCAL_APPS