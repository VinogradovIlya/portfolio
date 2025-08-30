"""
Django settings module initialization.
Automatically loads the appropriate settings based on DJANGO_SETTINGS_MODULE.
"""

import os

environment = os.environ.get('DJANGO_ENVIRONMENT', 'development')

if environment == 'production':
    from .production import *
elif environment == 'testing':
    from .testing import *
else:
    from .development import *
