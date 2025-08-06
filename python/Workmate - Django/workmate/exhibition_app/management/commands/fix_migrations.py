from django.core.management.base import BaseCommand
from django.core.management import call_command
from django.db import connection
import os

class Command(BaseCommand):
    help = 'Исправляет проблемы с миграциями и настраивает базу данных'

    def add_arguments(self, parser):
        parser.add_argument(
            '--force',
            action='store_true',
            help='Принудительно пересоздать миграции'
        )
        parser.add_argument(
            '--reset',
            action='store_true',
            help='Сбросить базу данных и создать заново'
        )

    def handle(self, *args, **options):
        force = options['force']
        reset = options['reset']

        self.stdout.write('🔧 Проверка и исправление миграций...')

        if reset:
            self.stdout.write('⚠️  Сброс базы данных...')
            self.reset_database()
        
        # Применяем все миграции
        self.stdout.write('📦 Применение миграций...')
        try:
            call_command('migrate', verbosity=0)
            self.stdout.write(self.style.SUCCESS('✅ Миграции применены успешно!'))
        except Exception as e:
            self.stdout.write(self.style.ERROR(f'❌ Ошибка при применении миграций: {e}'))
            return

        # Проверяем статус миграций
        self.stdout.write('🔍 Проверка статуса миграций...')
        try:
            call_command('showmigrations', verbosity=0)
            self.stdout.write(self.style.SUCCESS('✅ Все миграции применены!'))
        except Exception as e:
            self.stdout.write(self.style.ERROR(f'❌ Ошибка при проверке миграций: {e}'))

        # Создаем суперпользователя если его нет
        self.stdout.write('👤 Проверка суперпользователя...')
        try:
            from django.contrib.auth.models import User
            if not User.objects.filter(is_superuser=True).exists():
                self.stdout.write('Создание суперпользователя...')
                call_command('createsuperuser', interactive=False, username='admin', email='admin@example.com')
                self.stdout.write(self.style.SUCCESS('✅ Суперпользователь создан (admin/admin@example.com)'))
            else:
                self.stdout.write(self.style.SUCCESS('✅ Суперпользователь уже существует'))
        except Exception as e:
            self.stdout.write(self.style.WARNING(f'⚠️  Не удалось создать суперпользователя: {e}'))

        self.stdout.write(self.style.SUCCESS('🎉 Настройка миграций завершена!'))

    def reset_database(self):
        """Сброс базы данных"""
        try:
            # Удаляем файл базы данных SQLite
            db_path = 'db.sqlite3'
            if os.path.exists(db_path):
                os.remove(db_path)
                self.stdout.write('🗑️  База данных удалена')
            
            # Удаляем все файлы миграций кроме __init__.py
            migrations_dir = 'exhibition_app/migrations'
            for file in os.listdir(migrations_dir):
                if file.endswith('.py') and file != '__init__.py':
                    os.remove(os.path.join(migrations_dir, file))
                    self.stdout.write(f'🗑️  Удалена миграция: {file}')
            
            # Создаем новую миграцию
            call_command('makemigrations', 'exhibition_app', verbosity=0)
            self.stdout.write('📝 Создана новая миграция')
            
        except Exception as e:
            self.stdout.write(self.style.ERROR(f'❌ Ошибка при сбросе базы данных: {e}'))

    def check_database_connection(self):
        """Проверка подключения к базе данных"""
        try:
            with connection.cursor() as cursor:
                cursor.execute("SELECT 1")
                return True
        except Exception as e:
            self.stdout.write(self.style.ERROR(f'❌ Ошибка подключения к базе данных: {e}'))
            return False 