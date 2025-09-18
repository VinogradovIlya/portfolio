# frontend/views.py - обновляем существующий файл
from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth import authenticate, login as auth_login, logout as auth_logout
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.http import JsonResponse
from accounts.models import User
from accounts.serializers import UserRegistrationSerializer
from pets.models import Pet, Breed
from pets.serializers import PetCreateSerializer


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


@login_required
def pets_list_view(request):
    """Список питомцев пользователя"""
    pets = Pet.objects.filter(owner=request.user).order_by('-created_at')
    return render(request, 'frontend/pets/list.html', {'pets': pets})


@login_required
def pet_create_view(request):
    """Создание нового питомца"""
    if request.method == 'POST':
        # Получаем breed_id из формы
        breed_id = request.POST.get('breed')
        
        if breed_id:
            try:
                breed = Breed.objects.get(id=breed_id)
                
                # Создаем данные для сериализатора
                pet_data = request.POST.copy()
                pet_data['breed'] = breed.id
                
                serializer = PetCreateSerializer(
                    data=pet_data, 
                    context={'request': request}
                )
                
                if serializer.is_valid():
                    pet = serializer.save()
                    messages.success(request, f'Питомец {pet.name} успешно добавлен!')
                    return redirect('frontend:pets_list')
                else:
                    for field, errors in serializer.errors.items():
                        for error in errors:
                            messages.error(request, f"{field}: {error}")
            except Breed.DoesNotExist:
                messages.error(request, 'Выбранная порода не найдена')
        else:
            messages.error(request, 'Пожалуйста, выберите породу')
    
    return render(request, 'frontend/pets/create.html')


@login_required
def pet_edit_view(request, pet_id):
    """Редактирование питомца"""
    pet = get_object_or_404(Pet, id=pet_id, owner=request.user)
    
    if request.method == 'POST':
        breed_id = request.POST.get('breed')
        
        if breed_id:
            try:
                breed = Breed.objects.get(id=breed_id)
                
                pet_data = request.POST.copy()
                pet_data['breed'] = breed.id
                
                serializer = PetCreateSerializer(
                    pet, 
                    data=pet_data, 
                    partial=True
                )
                
                if serializer.is_valid():
                    pet = serializer.save()
                    messages.success(request, f'Данные питомца {pet.name} обновлены!')
                    return redirect('frontend:pets_list')
                else:
                    for field, errors in serializer.errors.items():
                        for error in errors:
                            messages.error(request, f"{field}: {error}")
            except Breed.DoesNotExist:
                messages.error(request, 'Выбранная порода не найдена')
        else:
            messages.error(request, 'Пожалуйста, выберите породу')
    
    context = {
        'pet': pet,
        'breeds': Breed.objects.all().order_by('species', 'name')
    }
    return render(request, 'frontend/pets/edit.html', context)


# API endpoint для получения пород по виду животного
@login_required
def get_breeds_by_species(request):
    """AJAX endpoint для получения пород по виду животного"""
    species = request.GET.get('species')
    
    if species:
        breeds = Breed.objects.filter(species=species).values('id', 'name')
        return JsonResponse({'breeds': list(breeds)})
    
    return JsonResponse({'breeds': []})