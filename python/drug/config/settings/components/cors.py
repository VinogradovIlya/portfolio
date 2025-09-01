"""
CORS configuration for API.
"""

# CORS settings
CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",  # React dev server
    "http://localhost:8080",  # Vue dev server
    "http://127.0.0.1:3000",
    "http://127.0.0.1:8080",
]

CORS_ALLOWED_ORIGIN_REGEXES = [
    r"^http://localhost:\d+$",
    r"^http://127\.0\.0\.1:\d+$",
]

CORS_ALLOW_CREDENTIALS = True

CORS_ALLOWED_HEADERS = [
    'accept',
    'accept-encoding',
    'authorization',
    'content-type',
    'dnt',
    'origin',
    'user-agent',
    'x-csrftoken',
    'x-requested-with',
]