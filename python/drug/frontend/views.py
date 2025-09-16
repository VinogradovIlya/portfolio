from django.shortcuts import render, redirect
from django.contrib.auth import authenticate, login as auth_login, logout as auth_logout
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from accounts.models import User, UserProfile
from pets.models import Pet, Breed
from accounts.serializers import UserRegistrationSerializer

def home_view(request):
    """Главная страница"""
    return render(request, 'frontend/home.html')

def register_view(request):
    """Страница регистрации"""
    if request.method == 'POST':
        serializer = UserRegistrationSerializer(data=request.POST)
        if serializer.is_valid():
            user = serializer.save()
            auth_login(request, user)
            messages.success(request, 'Регистрация прошла успешно!')
            return redirect('frontend:profile')
        else:
            for field, errors in serializer.errors.items():
                if isinstance(errors, list):
                    for error in errors:
                        messages.error(request, f"{field}: {error}")
                else:
                    messages.error(request, f"{field}: {errors}")
    
    return render(request, 'frontend/auth/register.html')

def login_view(request):
    """Страница входа"""
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
    """Выход"""
    auth_logout(request)
    messages.success(request, 'До свидания!')
    return redirect('frontend:home')

@login_required
def profile_view(request):
    """Профиль пользователя"""
    if request.method == 'POST':
        # Обновляем основные поля пользователя
        user = request.user
        user.city = request.POST.get('city', user.city)
        user.save()
        
        # Обновляем или создаем профиль
        profile, created = UserProfile.objects.get_or_create(user=user)
        profile.first_name = request.POST.get('first_name', profile.first_name)
        profile.last_name = request.POST.get('last_name', profile.last_name)
        profile.bio = request.POST.get('bio', profile.bio)
        profile.save()
        
        messages.success(request, 'Профиль обновлен!')
    
    return render(request, 'frontend/profile.html')

@login_required 
def pets_list_view(request):
    """Список питомцев пользователя"""
    pets = Pet.objects.filter(owner=request.user).select_related('breed')
    return render(request, 'frontend/pets/list.html', {'pets': pets})

@login_required
def pet_create_view(request):
    """Создание нового питомца"""
    breeds = Breed.objects.all()
    print(breeds)
    
    if request.method == 'POST':
        try:
            # Получаем данные из формы
            name = request.POST.get('name')
            breed_id = request.POST.get('breed')
            birthday = request.POST.get('birthday')
            gender = request.POST.get('gender')
            color = request.POST.get('color')
            weight = request.POST.get('weight')
            description = request.POST.get('description')
            
            # Валидация обязательных полей
            if not all([name, breed_id, birthday, gender, color]):
                messages.error(request, 'Заполните все обязательные поля')
                return render(request, 'frontend/pets/create.html', {'breeds': breeds})
            
            # Получаем породу
            breed = Breed.objects.get(id=breed_id)
            
            # Создаем питомца
            pet = Pet.objects.create(
                owner=request.user,
                name=name,
                breed=breed,
                birthday=birthday,
                gender=gender,
                color=color,
                weight=weight if weight else None,
                description=description or ''
            )
            
            messages.success(request, f'Питомец {pet.name} успешно добавлен!')
            return redirect('frontend:pets_list')
            
        except Breed.DoesNotExist:
            messages.error(request, 'Выбранная порода не найдена')
        except Exception as e:
            messages.error(request, f'Ошибка при создании питомца: {str(e)}')
    
    return render(request, 'frontend/pets/create.html', {'breeds': breeds})

@login_required
def pet_edit_view(request, pet_id):
    """Редактирование питомца"""
    try:
        pet = Pet.objects.get(id=pet_id, owner=request.user)
    except Pet.DoesNotExist:
        messages.error(request, 'Питомец не найден')
        return redirect('frontend:pets_list')
    
    breeds = Breed.objects.all()
    
    if request.method == 'POST':
        try:
            # Обновляем данные питомца
            pet.name = request.POST.get('name', pet.name)
            breed_id = request.POST.get('breed')
            if breed_id:
                pet.breed = Breed.objects.get(id=breed_id)
            pet.birthday = request.POST.get('birthday', pet.birthday)
            pet.gender = request.POST.get('gender', pet.gender)
            pet.color = request.POST.get('color', pet.color)
            
            weight = request.POST.get('weight')
            pet.weight = weight if weight else None
            
            pet.description = request.POST.get('description', pet.description)
            pet.save()
            
            messages.success(request, f'Питомец {pet.name} обновлен!')
            return redirect('frontend:pets_list')
            
        except Breed.DoesNotExist:
            messages.error(request, 'Выбранная порода не найдена')
        except Exception as e:
            messages.error(request, f'Ошибка при обновлении: {str(e)}')
    
    return render(request, 'frontend/pets/edit.html', {
        'pet': pet, 
        'breeds': breeds
    })

@login_required
def pet_delete_view(request, pet_id):
    """Удаление питомца"""
    try:
        pet = Pet.objects.get(id=pet_id, owner=request.user)
        pet_name = pet.name
        pet.delete()
        messages.success(request, f'Питомец {pet_name} удален')
    except Pet.DoesNotExist:
        messages.error(request, 'Питомец не найден')
    
    return redirect('frontend:pets_list')