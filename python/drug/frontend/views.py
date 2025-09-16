# frontend/views.py - замени на чистый Django подход
from django.shortcuts import render, redirect
from django.contrib.auth import authenticate, login as auth_login, logout as auth_logout
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from accounts.models import User
from accounts.serializers import UserRegistrationSerializer

def register_view(request):
    if request.method == 'POST':
        serializer = UserRegistrationSerializer(data=request.POST)
        if serializer.is_valid():
            user = serializer.save()
            auth_login(request, user)
            messages.success(request, 'Регистрация прошла успешно!')
            return redirect('frontend:profile')
        else:
            for field, errors in serializer.errors.items():
                for error in errors:
                    messages.error(request, f"{field}: {error}")
    
    return render(request, 'frontend/auth/register.html')

def login_view(request):
    if request.method == 'POST':
        email = request.POST.get('email')
        password = request.POST.get('password')
        
        user = authenticate(request, email=email, password=password)
        if user:
            auth_login(request, user)
            messages.success(request, 'Добро пожаловать!')
            return redirect('frontend:profile')
        else:
            messages.error(request, 'Неверный email или пароль')
    
    return render(request, 'frontend/auth/login.html')

def logout_view(request):
    auth_logout(request)
    messages.success(request, 'До свидания!')
    return redirect('frontend:home')

@login_required
def profile_view(request):
    if request.method == 'POST':
        # Обновляем основные поля пользователя
        user = request.user
        user.city = request.POST.get('city', user.city)
        user.save()
        
        # Обновляем профиль
        from accounts.models import UserProfile
        profile, created = UserProfile.objects.get_or_create(user=user)
        profile.first_name = request.POST.get('first_name', profile.first_name)
        profile.last_name = request.POST.get('last_name', profile.last_name)
        profile.bio = request.POST.get('bio', profile.bio)
        profile.save()
        
        messages.success(request, 'Профиль обновлен!')
    
    return render(request, 'frontend/profile.html')

def home_view(request):
    """Главная страница"""
    return render(request, 'frontend/home.html')