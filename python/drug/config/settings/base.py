# config/settings/base.py
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
import environ

BASE_DIR = Path(__file__).resolve().parent.parent.parent

env = environ.Env(
    SECRET_KEY=(str, 'django-insecure-change-me-in-production'),
    DEBUG=(bool, False),
    TELEGRAM_API_ID=(int, 0),
    TELEGRAM_API_HASH=(str, ''),
    TELEGRAM_BOT_TOKEN=(str, ''),
)

environ.Env.read_env(BASE_DIR / '.env')

SECRET_KEY = env('SECRET_KEY')
DEBUG = env('DEBUG')

LANGUAGE_CODE = 'ru-RU'
TIME_ZONE = 'Europe/Moscow'
USE_I18N = True
USE_TZ = True

DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'

AUTH_USER_MODEL = 'accounts.User'

TELEGRAM_API_ID = env('TELEGRAM_API_ID')
TELEGRAM_API_HASH = env('TELEGRAM_API_HASH') 
TELEGRAM_BOT_TOKEN = env('TELEGRAM_BOT_TOKEN')