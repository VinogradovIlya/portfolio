from django.core.management.base import BaseCommand
from core.models import Project, Skill


class Command(BaseCommand):
    help = 'init db'

    def handle(self, *args, **options):
        python = Skill.objects.create(
            name='Python', description='Python', years_experiens=3)
        sql = Skill.objects.create(
            name='SQL', description='PostgresSQL/Django ORM/SQLAlchemy', years_experiens=2)
        c = Skill.objects.create(
            name='C/C++', description='C/C++', years_experiens=2)
        workmate = Project.objects.create(
            title='Тестовое задание для компании workmate',
            description='Необходимо было реализовать проект "выставка котят" с использование Django',
            category='Python',
            github_url='https://github.com/VinogradovIlya/portfolio/tree/main/python/Workmate%20-%20Django',
            )
