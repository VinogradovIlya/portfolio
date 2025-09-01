"""
Base Django settings for drug_backend project.
"""

from .components.cors import *
from .components.cache import *
from .components.celery import *
from .components.logging import *
from .components.media import *
from .components.auth import *
from .components.drf import *
from .components.db import *
from .components.apps import *
import os
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent.parent.parent


SECRET_KEY = os.environ.get(
    'SECRET_KEY',
    'django-insecure-change-me-in-production'
)

LANGUAGE_CODE = 'ru-RU'
TIME_ZONE = 'Europe/Moscow'
USE_I18N = True
USE_TZ = True

DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'

AUTH_USER_MODEL = 'accounts.User'
