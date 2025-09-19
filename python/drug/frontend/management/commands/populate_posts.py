# posts/management/commands/populate_posts.py
from django.core.management.base import BaseCommand
from django.utils import timezone
from accounts.models import User
from posts.models import Post
import random


class Command(BaseCommand):
    help = 'Создает тестовые посты для ленты новостей'

    def add_arguments(self, parser):
        parser.add_argument('--count', type=int, default=30, help='Количество постов для создания')

    def handle(self, *args, **options):
        count = options['count']
        
        # Создаем тестовых пользователей, если их мало
        if User.objects.count() < 5:
            test_users_data = [
                ('anna@example.com', 'Анна', 'Петрова', 'Москва'),
                ('dmitry@example.com', 'Дмитрий', 'Смирнов', 'Санкт-Петербург'),
                ('elena@example.com', 'Елена', 'Козлова', 'Екатеринбург'),
                ('sergey@example.com', 'Сергей', 'Волков', 'Новосибирск'),
                ('maria@example.com', 'Мария', 'Морозова', 'Казань'),
            ]
            
            created_users = []
            for email, first_name, last_name, city in test_users_data:
                user, created = User.objects.get_or_create(
                    email=email,
                    defaults={
                        'user_type': 'pet_owner',
                        'phone': f'+7916{random.randint(1000000, 9999999)}',
                        'city': city,
                        'is_verified': True
                    }
                )
                if created:
                    user.set_password('testpass123')
                    user.save()
                    
                    # Создаем профиль
                    from accounts.models import UserProfile
                    UserProfile.objects.get_or_create(
                        user=user,
                        defaults={
                            'first_name': first_name,
                            'last_name': last_name
                        }
                    )
                    created_users.append(user)
                    self.stdout.write(f'Создан пользователь: {user.email}')

        # Получаем всех пользователей
        users = list(User.objects.all())
        
        # Тестовые посты
        posts_content = [
            "Мой кот сегодня впервые попробовал новый корм и очень доволен! 😸",
            "Вчера ходили с собакой к ветеринару на плановый осмотр. Все отлично! 🐕‍🦺",
            "Наш хомячок научился новому трюку - теперь он может стоять на задних лапках! 🐹",
            "Сегодня купили новую игрушку для кота. Он играет уже третий час подряд! 🧸",
            "Наша собака спасла котенка во дворе. Такие же у нас герои живут дома! 🦸‍♂️",
            "Попугай выучил новое слово и теперь постоянно его повторяет. Соседи в восторге 😅",
            "Первый день нашего щенка дома. Он такой милый, но уже успел погрызть тапок! 🐶",
            "Кот принес 'подарок' - мышку. Спасибо, конечно, но мы бы обошлись... 🐭",
            "Сходили на выставку собак. Столько красивых пород, глаза разбегаются! 🏆",
            "Наш аквариум пополнился новыми рыбками. Теперь там настоящий подводный мир! 🐠",
            "Кролик сегодня первый раз вышел гулять на улицу. Был в полном восторге! 🐰",
            "Ветеринар похвалил нас за отличный уход за питомцем. Приятно слышать! 👩‍⚕️",
            "Наш кот освоил новое место для сна - теперь спит в коробке из-под обуви 📦",
            "Собака научилась приносить тапочки. Теперь каждое утро начинается с этого ритуала! 🥿",
            "Попугай подружился с котом. Теперь они вместе смотрят в окно на птиц 🐦",
            "Купили новый домик для хомячка. Он изучает все уголки уже целый день! 🏠",
            "Наша черепашка отложила яйца! Скоро у нас будет пополнение в семье 🥚",
            "Кот впервые увидел снег и был очень удивлен. Долго изучал белые хлопья ❄️",
            "Собака выучила команду 'дай лапу'. Теперь здоровается со всеми гостями 🐾",
            "Рыбки в аквариуме начали размножаться. Скоро понадобится аквариум побольше! 🐟",
            "Наш кот стал звездой Instagram! У него уже 100 подписчиков 📱",
            "Щенок первый раз поехал в машине. Смотрел в окно и виляв хвостом всю дорогу 🚗",
            "Попугай научился имитировать звук будильника. Теперь просыпаемся в 6 утра... ⏰",
            "Кролик обожает морковку, но сегодня предпочел яблоко. Видимо, решил разнообразить диету 🥕",
            "Наша собака подружилась с соседским котом. Теперь они спят вместе на веранде 😴",
            "Хомячок построил себе новое гнездышко из салфеток. Настоящий архитектор! 🏗️",
            "Кот поймал свой первый листочек! Осень - его любимое время года 🍂",
            "Ветеринар сказал, что наш питомец - один из самых здоровых, которых он видел 💪",
            "Попугай выучил мелодию из мультика и теперь напевает ее весь день 🎵",
            "Наша золотая рыбка дожила до 5 лет! Это настоящий рекорд для нашей семьи 🎂"
        ]
        
        created_count = 0
        
        for i in range(count):
            # Выбираем случайного пользователя
            author = random.choice(users)
            
            # Выбираем случайный контент
            content = random.choice(posts_content)
            
            # Создаем пост
            post = Post.objects.create(
                author=author,
                content=content,
                likes_count=random.randint(0, 50),
                dislikes_count=random.randint(0, 5)
            )
            
            # Случайно добавляем лайки от других пользователей
            likers = random.sample(users, k=min(post.likes_count, len(users)))
            for liker in likers:
                if liker != author:
                    post.liked_by.add(liker)
            
            # Обновляем время создания (случайное время за последние 30 дней)
            random_days_ago = random.randint(0, 30)
            random_hours_ago = random.randint(0, 23)
            post.created_at = timezone.now() - timezone.timedelta(
                days=random_days_ago, 
                hours=random_hours_ago
            )
            post.save()
            
            created_count += 1
            
            if created_count % 10 == 0:
                self.stdout.write(f'Создано {created_count} постов...')
        
        self.stdout.write(
            self.style.SUCCESS(
                f'Успешно создано {created_count} тестовых постов от {len(users)} пользователей'
            )
        )