from django.urls import path, include
from rest_framework.routers import DefaultRouter
from rest_framework_simplejwt.views import (
    TokenObtainPairView,
    TokenRefreshView,
    TokenVerifyView,
)
from .api_views import KittenOwnerViewSet, CatViewSet, RatingViewSet, ImagesViewSet
from .jwt_views import register, login, logout, profile

# Создаем роутер для ViewSets
router = DefaultRouter()
router.register(r'owners', KittenOwnerViewSet)
router.register(r'cats', CatViewSet)
router.register(r'ratings', RatingViewSet)
router.register(r'images', ImagesViewSet)

# API URL patterns
urlpatterns = [
    # ViewSets
    path('', include(router.urls)),
    
    # JWT Authentication
    path('auth/register/', register, name='api_register'),
    path('auth/login/', login, name='api_login'),
    path('auth/logout/', logout, name='api_logout'),
    path('auth/profile/', profile, name='api_profile'),
    
    # JWT Token endpoints
    path('auth/token/', TokenObtainPairView.as_view(), name='token_obtain_pair'),
    path('auth/token/refresh/', TokenRefreshView.as_view(), name='token_refresh'),
    path('auth/token/verify/', TokenVerifyView.as_view(), name='token_verify'),
] 