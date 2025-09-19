# frontend/views.py
from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth import authenticate, login as auth_login, logout as auth_logout
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.http import JsonResponse
from django.core.paginator import Paginator
from accounts.models import User
from accounts.serializers import UserRegistrationSerializer
from pets.models import Pet, Breed
from pets.serializers import PetCreateSerializer
from posts.models import Post


def check_user_profile_complete(user):
    """
    Проверяет, заполнен ли профиль пользователя
    Возвращает True если профиль заполнен, False если нет
    """
    try:
        profile = user.profile
        return bool(profile.first_name and profile.last_name)
    except:
        return False


def redirect_based_on_profile(user, default_redirect='frontend:posts_feed'):
    """
    Перенаправляет пользователя в зависимости от состояния профиля
    """
    if check_user_profile_complete(user):
        return redirect(default_redirect)
    else:
        return redirect('frontend:profile')


def register_view(request):
    if request.method == 'POST':
        serializer = UserRegistrationSerializer(data=request.POST)
        if serializer.is_valid():
            user = serializer.save()
            auth_login(request, user)
            messages.success(request, 'Регистрация прошла успешно! Пожалуйста, заполните информацию о себе.')
            # Всегда идем на заполнение профиля после регистрации
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
            
            # Проверяем, заполнен ли профиль
            try:
                profile = user.profile
                # Проверяем, заполнены ли основные поля профиля
                if profile.first_name and profile.last_name:
                    # Профиль заполнен - идем в ленту
                    return redirect('frontend:posts_feed')
                else:
                    # Профиль не заполнен - идем на редактирование
                    messages.info(request, 'Пожалуйста, заполните информацию о себе')
                    return redirect('frontend:profile')
            except:
                # Профиль не существует - идем на его создание
                messages.info(request, 'Пожалуйста, заполните информацию о себе')
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
        
        # Сохраняем старые значения для проверки
        was_empty = not (profile.first_name and profile.last_name)
        
        profile.first_name = request.POST.get('first_name', profile.first_name)
        profile.last_name = request.POST.get('last_name', profile.last_name)
        profile.bio = request.POST.get('bio', profile.bio)
        profile.save()
        
        messages.success(request, 'Профиль обновлен!')
        
        # Если профиль был пустой и теперь заполнен - перенаправляем в ленту
        if was_empty and profile.first_name and profile.last_name:
            messages.success(request, 'Отлично! Теперь вы можете создавать посты и общаться с сообществом.')
            return redirect('frontend:posts_feed')
    
    # Получаем последние 5 постов пользователя
    user_posts = Post.objects.filter(author=request.user).order_by('-created_at')[:5]
    
    context = {
        'user_posts': user_posts
    }
    return render(request, 'frontend/profile.html', context)


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


@login_required
def posts_feed_view(request):
    """Лента постов/новостей"""
    # Проверяем, заполнен ли профиль
    if not check_user_profile_complete(request.user):
        messages.info(request, 'Для доступа к ленте постов необходимо заполнить профиль')
        return redirect('frontend:profile')
    
    posts_list = Post.objects.all().select_related('author__profile').prefetch_related('photos').order_by('-created_at')
    
    paginator = Paginator(posts_list, 10)  # 10 постов на страницу
    page_number = request.GET.get('page')
    posts = paginator.get_page(page_number)
    
    return render(request, 'frontend/posts/feed.html', {'posts': posts})


@login_required
def create_post_view(request):
    """Создание нового поста"""
    if request.method == 'POST':
        content = request.POST.get('content', '').strip()
        
        if content:
            post = Post.objects.create(
                author=request.user,
                content=content
            )
            
            # Обработка фотографий (если есть)
            photos = request.FILES.getlist('photos')
            for photo in photos:
                from posts.models import PostPhoto
                PostPhoto.objects.create(post=post, photo=photo)
            
            messages.success(request, 'Пост успешно опубликован!')
        else:
            messages.error(request, 'Содержание поста не может быть пустым')
    
    return redirect('frontend:posts_feed')


@login_required
def user_posts_view(request, user_id):
    """Все посты конкретного пользователя"""
    user = get_object_or_404(User, id=user_id)
    posts_list = Post.objects.filter(author=user).select_related('author__profile').prefetch_related('photos').order_by('-created_at')
    
    paginator = Paginator(posts_list, 10)
    page_number = request.GET.get('page')
    posts = paginator.get_page(page_number)
    
    context = {
        'posts': posts,
        'posts_user': user,
    }
    return render(request, 'frontend/posts/user_posts.html', context)


def under_construction_view(request):
    """Страница-заглушка для функционала в разработке"""
    return render(request, 'frontend/under_construction.html')


# API endpoint для получения пород по виду животного
@login_required
def get_breeds_by_species(request):
    """AJAX endpoint для получения пород по виду животного"""
    species = request.GET.get('species')
    
    if species:
        breeds = Breed.objects.filter(species=species).values('id', 'name')
        return JsonResponse({'breeds': list(breeds)})
    
    return JsonResponse({'breeds': []})