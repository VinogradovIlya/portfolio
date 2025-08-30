"""
Cache configuration.
"""

import os

CACHES = {
    'default': {
        'BACKEND': 'django.core.cache.backends.redis.RedisCache',
        'LOCATION': os.environ.get('REDIS_URL', 'redis://localhost:6379/1'),
        'KEY_PREFIX': 'drug_backend',
        'TIMEOUT': 300,  # 5 minutes default timeout
        'OPTIONS': {
            'CLIENT_CLASS': 'django_redis.client.DefaultClient',
        }
    }
}

# Cache timeouts
CACHE_TIMEOUTS = {
    'short': 300,      # 5 minutes
    'medium': 1800,    # 30 minutes
    'long': 3600,      # 1 hour
    'very_long': 86400, # 1 day
}