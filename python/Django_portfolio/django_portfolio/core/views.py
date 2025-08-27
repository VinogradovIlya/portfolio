from django.shortcuts import render
from django.db.models import Q
from .models import Project, Skill, Technologies

# Create your views here.


def home(request):
    count = Project.objects.all().count()
    context = {
        'photo': 'core/images/profile_new.jpg',  # путь к твоей фотографии
        'name': 'Илья',
        'surname': 'Виноградов',
        'number': count,
    }
    return render(request, 'core/index.html', context)


def projects(request):
    search_query = request.GET.get('search', '')
    category_filter = request.GET.get('category', 'all')

    projects = Project.objects.all()
    technologies = Technologies.objects.all()

    if search_query:
        projects = projects.filter(
            Q(title__icontains=search_query) |
            Q(description__icontains=search_query)
        )

    if category_filter != 'all':
        projects = projects.filter(category=category_filter)

    project_categories = Project.CATEGORY_CHOICES
    project_technologies = Technologies.CATEGORY_CHOICES

    context = {
        'photo': 'core/images/profile.jpg',
        'projects': projects,
        # 'technologies': technologies,
        'skills': Skill.objects.all(),
        'search_query': search_query,
        'current_category': category_filter,
        'project_categories': project_categories,
        'project_technologies': project_technologies,
    }

    return render(request, 'core/projects.html', context)

def contact(request):
    context = {
        'name': 'Илья',
        'surname': 'Виноградов',
        'photo': 'core/images/profile_new.jpg',  # Путь к фото в static файлах
        'phone': '+7 (926) 000 80 22',
        'mail': 'vivpost@mail.ru',
        'tg': '@vivpost',
        'description': 'Python разработчик с опытом создания веб-приложений на Django. Специализируюсь на разработке полнофункциональных веб-сайтов, API и автоматизации процессов.',
        'github': 'https://github.com/VinogradovIlya/portfolio',
        'position': 'Python Developer',
        'skills': Skill.objects.all(),
    }
    return render(request, 'core/contact.html', context)