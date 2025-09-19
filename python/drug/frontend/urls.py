from django.urls import path
from . import views

app_name = 'frontend'

urlpatterns = [
    path('', views.home_view, name='home'),
    path('register/', views.register_view, name='register'),
    path('login/', views.login_view, name='login'),
    path('logout/', views.logout_view, name='logout'),
    path('profile/', views.profile_view, name='profile'),
    
    # Питомцы
    path('pets/', views.pets_list_view, name='pets_list'),
    path('pets/create/', views.pet_create_view, name='pet_create'),
    path('pets/<int:pet_id>/edit/', views.pet_edit_view, name='pet_edit'),
    
    # Посты/Лента новостей
    path('feed/', views.posts_feed_view, name='posts_feed'),
    path('posts/create/', views.create_post_view, name='create_post'),
    path('user/<int:user_id>/posts/', views.user_posts_view, name='user_posts'),
    
    # Страница-заглушка
    path('under-construction/', views.under_construction_view, name='under_construction'),
    
    # AJAX endpoints
    path('api/breeds/', views.get_breeds_by_species, name='get_breeds'),
]