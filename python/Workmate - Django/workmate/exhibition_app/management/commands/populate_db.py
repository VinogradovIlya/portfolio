from django.core.management.base import BaseCommand
from django.core.files.base import ContentFile
from django.db import transaction
import random
from exhibition_app.models import KittenOwner, Cat, Rating, Images

class Command(BaseCommand):
    help = 'Заполняет базу данных тестовыми данными о кошках и владельцах'

    def add_arguments(self, parser):
        parser.add_argument(
            '--owners',
            type=int,
            default=10,
            help='Количество владельцев для создания (по умолчанию: 10)'
        )
        parser.add_argument(
            '--cats',
            type=int,
            default=20,
            help='Количество кошек для создания (по умолчанию: 20)'
        )
        parser.add_argument(
            '--ratings',
            type=int,
            default=50,
            help='Количество оценок для создания (по умолчанию: 50)'
        )
        parser.add_argument(
            '--clear',
            action='store_true',
            help='Очистить существующие данные перед заполнением'
        )

    def handle(self, *args, **options):
        owners_count = options['owners']
        cats_count = options['cats']
        ratings_count = options['ratings']
        clear_data = options['clear']

        if clear_data:
            self.stdout.write('Очистка существующих данных...')
            Rating.objects.all().delete()
            Images.objects.all().delete()
            Cat.objects.all().delete()
            KittenOwner.objects.all().delete()
            self.stdout.write(self.style.SUCCESS('Данные очищены!'))

        with transaction.atomic():
            # Создаем владельцев
            self.stdout.write(f'Создание {owners_count} владельцев...')
            owners = self.create_owners(owners_count)
            self.stdout.write(self.style.SUCCESS(f'Создано {len(owners)} владельцев!'))

            # Создаем кошек
            self.stdout.write(f'Создание {cats_count} кошек...')
            cats = self.create_cats(cats_count, owners)
            self.stdout.write(self.style.SUCCESS(f'Создано {len(cats)} кошек!'))

            # Создаем оценки
            self.stdout.write(f'Создание {ratings_count} оценок...')
            ratings = self.create_ratings(ratings_count, cats, owners)
            self.stdout.write(self.style.SUCCESS(f'Создано {len(ratings)} оценок!'))

        self.stdout.write(self.style.SUCCESS('База данных успешно заполнена тестовыми данными!'))

    def create_owners(self, count):
        """Создает тестовых владельцев кошек"""
        first_names = [
            'Александр', 'Мария', 'Дмитрий', 'Анна', 'Сергей', 'Елена', 'Андрей', 'Ольга',
            'Владимир', 'Татьяна', 'Игорь', 'Наталья', 'Михаил', 'Ирина', 'Николай', 'Светлана',
            'Павел', 'Юлия', 'Артем', 'Ангелина', 'Роман', 'Кристина', 'Денис', 'Марина',
            'Алексей', 'Екатерина', 'Максим', 'Виктория', 'Иван', 'Алиса'
        ]
        
        last_names = [
            'Иванов', 'Петров', 'Сидоров', 'Смирнов', 'Кузнецов', 'Попов', 'Васильев', 'Соколов',
            'Михайлов', 'Новиков', 'Федоров', 'Морозов', 'Волков', 'Алексеев', 'Лебедев', 'Семенов',
            'Егоров', 'Павлов', 'Козлов', 'Степанов', 'Николаев', 'Орлов', 'Андреев', 'Макаров',
            'Никитин', 'Захаров', 'Зайцев', 'Соловьев', 'Борисов', 'Яковлев'
        ]
        
        middle_names = [
            'Александрович', 'Александровна', 'Дмитриевич', 'Дмитриевна', 'Сергеевич', 'Сергеевна',
            'Андреевич', 'Андреевна', 'Владимирович', 'Владимировна', 'Игоревич', 'Игоревна',
            'Михайлович', 'Михайловна', 'Николаевич', 'Николаевна', 'Павлович', 'Павловна',
            'Романович', 'Романовна', 'Денисович', 'Денисовна', 'Алексеевич', 'Алексеевна',
            'Максимович', 'Максимовна', 'Иванович', 'Ивановна', 'Артемович', 'Артемовна'
        ]

        owners = []
        for i in range(count):
            first_name = random.choice(first_names)
            last_name = random.choice(last_names)
            middle_name = random.choice(middle_names)
            
            owner = KittenOwner.objects.create(
                name=first_name,
                surname=last_name,
                patronymic=middle_name
            )
            owners.append(owner)
        
        return owners

    def create_cats(self, count, owners):
        """Создает тестовых кошек"""
        breeds = [
            'Сиамская', 'Персидская', 'Мейн-кун', 'Британская короткошерстная', 'Русская голубая',
            'Абиссинская', 'Бенгальская', 'Рэгдолл', 'Сфинкс', 'Норвежская лесная',
            'Сибирская', 'Турецкая ангора', 'Бирманская', 'Ориентальная', 'Корниш-рекс',
            'Девон-рекс', 'Американская короткошерстная', 'Египетская мау', 'Тонкинская', 'Балинезийская'
        ]
        
        colors = [
            'Черный', 'Белый', 'Серый', 'Рыжий', 'Трехцветный', 'Двухцветный', 'Полосатый',
            'Пятнистый', 'Дымчатый', 'Кремовый', 'Голубой', 'Шоколадный', 'Лиловый', 'Коричневый',
            'Золотистый', 'Серебристый', 'Черепаховый', 'Калико', 'Табби', 'Сиамский окрас'
        ]
        
        descriptions = [
            'Очень ласковый и игривый котенок. Любит детей и других животных.',
            'Спокойный и уравновешенный характер. Отлично подходит для семьи.',
            'Энергичный и любознательный. Всегда найдет чем заняться.',
            'Нежный и заботливый. Любит сидеть на коленях и мурлыкать.',
            'Умный и сообразительный. Быстро обучается новым трюкам.',
            'Дружелюбный и общительный. Хорошо ладит с другими кошками.',
            'Активный и подвижный. Любит игры и прогулки на свежем воздухе.',
            'Терпеливый и выносливый. Отлично подходит для активных семей.',
            'Любопытный и исследователь. Всегда изучает новые места.',
            'Верный и преданный. Станет лучшим другом для всей семьи.',
            'Элегантный и грациозный. Поражает своей красотой и изяществом.',
            'Веселый и жизнерадостный. Поднимет настроение в любой день.',
            'Мудрый и рассудительный. Всегда знает, когда нужна поддержка.',
            'Игривый и забавный. Принесет много радости и смеха.',
            'Нежный и чувствительный. Понимает настроение хозяина.'
        ]

        cats = []
        for i in range(count):
            breed = random.choice(breeds)
            color = random.choice(colors)
            description = random.choice(descriptions)
            age = random.randint(2, 24)  # Возраст от 2 до 24 месяцев
            owner = random.choice(owners)
            
            # Создаем простое тестовое изображение
            image_content = self.create_test_image()
            
            cat = Cat.objects.create(
                colors=color,
                mounts=age,
                kitten_breed=breed,
                description=description,
                photo=ContentFile(image_content, name=f'cat_{i+1}.jpg'),
                kitten_owner=owner
            )
            cats.append(cat)
        
        return cats

    def create_ratings(self, count, cats, owners):
        """Создает тестовые оценки"""
        ratings = []
        for i in range(count):
            cat = random.choice(cats)
            author = random.choice(owners)
            rating_value = random.randint(1, 5)
            
            # Проверяем, не существует ли уже такая оценка
            existing_rating = Rating.objects.filter(cat=cat, author=author).first()
            if existing_rating:
                existing_rating.rating = rating_value
                existing_rating.save()
                ratings.append(existing_rating)
            else:
                rating = Rating.objects.create(
                    cat=cat,
                    author=author,
                    rating=rating_value
                )
                ratings.append(rating)
        
        return ratings

    def create_test_image(self):
        """Создает простое тестовое изображение"""
        # Создаем минимальное JPEG изображение (1x1 пиксель)
        # Это заглушка для тестирования
        return b'\xff\xd8\xff\xe0\x00\x10JFIF\x00\x01\x01\x01\x00H\x00H\x00\x00\xff\xdb\x00C\x00\x08\x06\x06\x07\x06\x05\x08\x07\x07\x07\t\t\x08\n\x0c\x14\r\x0c\x0b\x0b\x0c\x19\x12\x13\x0f\x14\x1d\x1a\x1f\x1e\x1d\x1a\x1c\x1c $.\' ",#\x1c\x1c(7),01444\x1f\'9=82<.342\xff\xc0\x00\x11\x08\x00\x01\x00\x01\x01\x01\x11\x00\x02\x11\x01\x03\x11\x01\xff\xc4\x00\x14\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xff\xc4\x00\x14\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xda\x00\x0c\x03\x01\x00\x02\x11\x03\x11\x00\x3f\x00\xaa\xff\xd9' 