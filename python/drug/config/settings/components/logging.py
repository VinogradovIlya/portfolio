"""
Logging configuration.
"""

import os
from pathlib import Path


BASE_DIR = Path(__file__).resolve().parent.parent.parent.parent

LOGGING = {
    'version': 1,
    'disable_existing_loggers': False,
    'formatters': {
        'verbose': {
            'format': '{levelname} {asctime} {module} {process:d} {thread:d} {message}',
            'style': '{',
        },
        'simple': {
            'format': '{levelname} {message}',
            'style': '{',
        },
    },
    'handlers': {
        'file': {
            'level': 'INFO',
            'class': 'logging.FileHandler',
            'filename': os.path.join(BASE_DIR, 'logs', 'django.log'),
            'formatter': 'verbose',
        },
        'console': {
            'level': 'DEBUG',
            'class': 'logging.StreamHandler',
            'formatter': 'simple',
        },
    },
    'root': {
        'handlers': ['console', 'file'],
        'level': 'INFO',
    },
    'loggers': {
        'django': {
            # 'handlers': ['console', 'file'],
            'handlers': ['file'],
            'level': 'INFO',
            'propagate': False,
        },
        'core': {
            # 'handlers': ['console', 'file'],
            'handlers': ['file'],
            'level': 'DEBUG',
            'propagate': False,
        },
    },
}
