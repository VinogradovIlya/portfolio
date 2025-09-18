from django.core.management.base import BaseCommand
from pets.models import Breed


class Command(BaseCommand):
    help = 'Заполняет базу данных породами животных'

    def handle(self, *args, **options):
        breeds_data = [
            # Собаки
            ('dog', 'Лабрадор'),
            ('dog', 'Немецкая овчарка'),
            ('dog', 'Золотистый ретривер'),
            ('dog', 'Французский бульдог'),
            ('dog', 'Бигль'),
            ('dog', 'Пудель'),
            ('dog', 'Хаски'),
            ('dog', 'Чихуахуа'),
            ('dog', 'Такса'),
            ('dog', 'Йоркширский терьер'),
            ('dog', 'Метис'),
            
            # Кошки
            ('cat', 'Британская короткошёрстная'),
            ('cat', 'Шотландская вислоухая'),
            ('cat', 'Мейн-кун'),
            ('cat', 'Персидская'),
            ('cat', 'Сиамская'),
            ('cat', 'Русская голубая'),
            ('cat', 'Абиссинская'),
            ('cat', 'Сфинкс'),
            ('cat', 'Бенгальская'),
            ('cat', 'Обычная домашняя'),
            
            # Птицы
            ('bird', 'Волнистый попугай'),
            ('bird', 'Корелла'),
            ('bird', 'Канарейка'),
            ('bird', 'Неразлучник'),
            ('bird', 'Жако'),
            
            # Грызуны
            ('rodent', 'Хомяк'),
            ('rodent', 'Крыса'),
            ('rodent', 'Морская свинка'),
            ('rodent', 'Шиншилла'),
            ('rodent', 'Дегу'),
            
            # Рыбы
            ('fish', 'Золотая рыбка'),
            ('fish', 'Гуппи'),
            ('fish', 'Неон'),
            ('fish', 'Скалярия'),
            ('fish', 'Петушок'),
            
            # Рептилии
            ('reptile', 'Красноухая черепаха'),
            ('reptile', 'Игуана'),
            ('reptile', 'Геккон'),
            ('reptile', 'Питон'),
        ]

        created_count = 0
        for species, name in breeds_data:
            breed, created = Breed.objects.get_or_create(
                species=species,
                name=name,
                defaults={'description': f'Порода {name}'}
            )
            if created:
                created_count += 1
                self.stdout.write(f'Создана порода: {breed}')

        self.stdout.write(
            self.style.SUCCESS(
                f'Успешно создано {created_count} новых пород'
            )
        )