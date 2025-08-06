from django.http import JsonResponse
from django.core.serializers.json import DjangoJSONEncoder
from django.shortcuts import get_object_or_404, render, redirect
from django.contrib import messages
from django.db import models

from .models import KittenOwner, Cat, Rating, Images

# Create your views here.


def home(request):
    cats_count = Cat.objects.count()
    owners_count = KittenOwner.objects.count()
    breeds_count = Cat.objects.values('kitten_breed').distinct().count()

    context = {
        'cats_count': cats_count,
        'owners_count': owners_count,
        'breeds_count': breeds_count,
    }
    return render(request, 'exhibition_app/home.html', context)


def add_owner(request):
    context = {}
    if request.method == 'POST':
        name = request.POST.get('name')
        surname = request.POST.get('surname')
        patronymic = request.POST.get('patronymic')

        if name and surname and patronymic:
            owner = KittenOwner.objects.create(
                name=name,
                surname=surname,
                patronymic=patronymic
            )
            context = {
                'message': f'Владелец {surname} {name} {patronymic} успешно добавлен!',
                'error': False
            }
        else:
            context = {
                'message': 'Пожалуйста, заполните все поля',
                'error': True
            }

    return render(request, 'exhibition_app/add_owner.html', context)


def add_cat(request):
    owners = KittenOwner.objects.all()
    context = {'owners': owners}

    if request.method == 'POST':
        colors = request.POST.get('colors')
        mounts = request.POST.get('mounts')
        kitten_breed = request.POST.get('kitten_breed')
        description = request.POST.get('description')
        photo = request.FILES.get('photo')
        kitten_owner_id = request.POST.get('kitten_owner')

        if all([colors, mounts, kitten_breed, description, photo, kitten_owner_id]):
            try:
                kitten_owner = KittenOwner.objects.get(id=kitten_owner_id)
                cat = Cat.objects.create(
                    colors=colors,
                    mounts=int(mounts),
                    kitten_breed=kitten_breed,
                    description=description,
                    photo=photo,
                    kitten_owner=kitten_owner
                )
                context = {
                    'message': f'Кошка породы {kitten_breed} успешно добавлена!',
                    'error': False,
                    'owners': owners
                }
            except KittenOwner.DoesNotExist:
                context = {
                    'message': 'Выбранный владелец не найден',
                    'error': True,
                    'owners': owners
                }
        else:
            context = {
                'message': 'Пожалуйста, заполните все поля',
                'error': True,
                'owners': owners
            }

    return render(request, 'exhibition_app/add_cat.html', context)


def edit_cat(request, pk):
    cat = get_object_or_404(Cat, pk=pk)
    owners = KittenOwner.objects.all()

    if request.method == 'POST':
        colors = request.POST.get('colors')
        mounts = request.POST.get('mounts')
        kitten_breed = request.POST.get('kitten_breed')
        description = request.POST.get('description')
        photo = request.FILES.get('photo')
        kitten_owner_id = request.POST.get('kitten_owner')

        if all([colors, mounts, kitten_breed, description, kitten_owner_id]):
            try:
                kitten_owner = KittenOwner.objects.get(id=kitten_owner_id)
                cat.colors = colors
                cat.mounts = int(mounts)
                cat.kitten_breed = kitten_breed
                cat.description = description
                cat.kitten_owner = kitten_owner

                if photo:
                    cat.photo = photo

                cat.save()
                context = {
                    'message': f'Кошка породы {kitten_breed} успешно обновлена!',
                    'error': False,
                    'cat': cat,
                    'owners': owners
                }
            except KittenOwner.DoesNotExist:
                context = {
                    'message': 'Выбранный владелец не найден',
                    'error': True,
                    'cat': cat,
                    'owners': owners
                }
        else:
            context = {
                'message': 'Пожалуйста, заполните все обязательные поля',
                'error': True,
                'cat': cat,
                'owners': owners
            }
    else:
        context = {
            'cat': cat,
            'owners': owners
        }

    return render(request, 'exhibition_app/edit_cat.html', context)


def delete_cat(request, pk):
    if request.method == 'POST':
        cat = get_object_or_404(Cat, pk=pk)
        cat.delete()
        return redirect('exhibition_app:list_cats')
    return redirect('exhibition_app:list_cats')


def list_cats(request):
    cats = Cat.objects.select_related('kitten_owner').all()
    
    # Добавляем информацию о рейтингах для каждой кошки
    for cat in cats:
        ratings = Rating.objects.filter(cat=cat)
        cat.ratings_count = ratings.count()
        if cat.ratings_count > 0:
            cat.average_rating = ratings.aggregate(avg=models.Avg('rating'))['avg']
        else:
            cat.average_rating = None
    
    context = {'cats': cats}
    return render(request, 'exhibition_app/list_cats.html', context)

def add_rating(request):
    cats = Cat.objects.select_related('kitten_owner').all()
    owners = KittenOwner.objects.all()
    
    # Если передан параметр cat, предвыбираем кошку
    selected_cat = request.GET.get('cat')
    
    if request.method == 'POST':
        cat_id = request.POST.get('cat')
        author_id = request.POST.get('author')
        rating_value = request.POST.get('rating')
        
        if all([cat_id, author_id, rating_value]):
            try:
                cat = Cat.objects.get(id=cat_id)
                author = KittenOwner.objects.get(id=author_id)
                
                # Проверяем, не оценивал ли уже этот пользователь эту кошку
                existing_rating = Rating.objects.filter(cat=cat, author=author).first()
                
                if existing_rating:
                    # Обновляем существующую оценку
                    existing_rating.rating = int(rating_value)
                    existing_rating.save()
                    message = f'Ваша оценка для {cat.kitten_breed} обновлена на {rating_value} звезд!'
                else:
                    # Создаем новую оценку
                    Rating.objects.create(
                        cat=cat,
                        author=author,
                        rating=int(rating_value)
                    )
                    message = f'Спасибо! Вы оценили {cat.kitten_breed} на {rating_value} звезд!'
                
                context = {
                    'message': message,
                    'error': False,
                    'cats': cats,
                    'owners': owners
                }
            except (Cat.DoesNotExist, KittenOwner.DoesNotExist):
                context = {
                    'message': 'Ошибка: кошка или владелец не найдены',
                    'error': True,
                    'cats': cats,
                    'owners': owners
                }
        else:
            context = {
                'message': 'Пожалуйста, заполните все поля',
                'error': True,
                'cats': cats,
                'owners': owners
            }
    else:
        context = {
            'cats': cats,
            'owners': owners,
            'selected_cat': selected_cat
        }
    
    return render(request, 'exhibition_app/add_rating.html', context)


def ratings(request):
    # Получаем кошек с рейтингами, отсортированных по среднему рейтингу
    cats_with_ratings = []
    
    for cat in Cat.objects.select_related('kitten_owner').all():
        ratings = Rating.objects.filter(cat=cat)
        cat.ratings_count = ratings.count()
        
        if cat.ratings_count > 0:
            cat.average_rating = ratings.aggregate(avg=models.Avg('rating'))['avg']
            # Получаем последние 3 оценки
            cat.recent_ratings = ratings.select_related('author').order_by('-id')[:3]
            cats_with_ratings.append(cat)
    
    # Сортируем по среднему рейтингу (по убыванию)
    cats_with_ratings.sort(key=lambda x: x.average_rating, reverse=True)
    
    context = {'cats_with_ratings': cats_with_ratings}
    return render(request, 'exhibition_app/ratings.html', context)


def all_cats(request, breed=None):
    if breed is None:
        breed = request.GET.get('breed')

    if breed is None:
        cats = Cat.objects.all()
        response_data = {'intro': 'All cats'}
    else:
        if not Cat.objects.filter(kitten_breed=breed).exists():
            return JsonResponse({
                'error': f'Cat with breed = {breed} not found'
            }, status=400)
        cats = Cat.objects.filter(kitten_breed=breed).values(
            'id',
            'color',
            'mounts',
            'kitten_breeds',
            'description',
            'photo',
            'kitten_owner'
        )
        response_data = {'intro': f'Cats of breed: {breed}', 'breed': breed}

    response_data['total_count'] = cats.count()
    response_data['cats'] = list(cats.values('id', 'colors', 'mounts', 'kitten_breed', 'description', 'photo', 'kitten_owner'
                                             ))
    return JsonResponse(response_data, encoder=DjangoJSONEncoder)


def kitten_breeds(request):
    breeds = Cat.objects.values_list('kitten_breed', flat=True).distinct()
    response_data = {
        'intro': 'All kitten breeds',
        'breeds_count': len(breeds),
        'kitten_breeds': list(breeds),
    }
    return JsonResponse(response_data, encoder=DjangoJSONEncoder)


def get_cat_info(request, pk=None):
    if pk is None:
        pk = request.GET.get('pk')

    if pk is None:
        return JsonResponse({'error': 'Cat ID is required'}, status=400)

    try:
        cat = get_object_or_404(Cat, pk=pk)
    except ValueError:
        return JsonResponse({'error': 'Invalid cat ID format'}, status=400)

    cat_data = {
        'id': cat.id,
        'colors': cat.colors,
        'mounts': cat.mounts,
        'kitten_breeds': cat.kitten_breed,
        'description': cat.description,
        'photo': cat.photo,
        'kitten_owner': cat.kitten_owner
    }
    response_data = {
        'intro': 'Getting information about a kitten',
        'cat': cat_data
    }

    return JsonResponse(response_data, encoder=DjangoJSONEncoder)
