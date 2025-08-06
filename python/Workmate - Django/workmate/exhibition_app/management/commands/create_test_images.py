from django.core.management.base import BaseCommand
from django.core.files.base import ContentFile
from PIL import Image, ImageDraw
import random
import io
from exhibition_app.models import Cat

class Command(BaseCommand):
    help = 'Создает реалистичные тестовые изображения для кошек'

    def add_arguments(self, parser):
        parser.add_argument(
            '--width',
            type=int,
            default=400,
            help='Ширина изображения (по умолчанию: 400)'
        )
        parser.add_argument(
            '--height',
            type=int,
            default=300,
            help='Высота изображения (по умолчанию: 300)'
        )
        parser.add_argument(
            '--cats',
            type=int,
            help='Количество кошек для обновления (по умолчанию: все)'
        )

    def handle(self, *args, **options):
        width = options['width']
        height = options['height']
        cats_limit = options['cats']

        cats = Cat.objects.all()
        if cats_limit:
            cats = cats[:cats_limit]

        self.stdout.write(f'Создание изображений для {cats.count()} кошек...')

        for i, cat in enumerate(cats):
            # Создаем изображение на основе породы и окраса кошки
            image = self.create_cat_image(cat, width, height)
            
            # Сохраняем в байты
            img_io = io.BytesIO()
            image.save(img_io, format='JPEG', quality=85)
            img_io.seek(0)
            
            # Обновляем фото кошки
            cat.photo.save(f'cat_{cat.id}_{cat.kitten_breed.lower().replace(" ", "_")}.jpg', 
                          ContentFile(img_io.getvalue()), save=True)
            
            if (i + 1) % 5 == 0:
                self.stdout.write(f'Обработано {i + 1} кошек...')

        self.stdout.write(self.style.SUCCESS(f'Создано {cats.count()} изображений!'))

    def create_cat_image(self, cat, width, height):
        """Создает изображение кошки на основе её характеристик"""
        # Создаем базовое изображение
        image = Image.new('RGB', (width, height), self.get_background_color(cat.colors))
        draw = ImageDraw.Draw(image)
        
        # Определяем цвета кошки на основе окраса
        cat_colors = self.get_cat_colors(cat.colors)
        
        # Рисуем тело кошки
        body_width = width // 2
        body_height = height // 2
        body_x = (width - body_width) // 2
        body_y = height // 3
        
        # Тело
        draw.ellipse([body_x, body_y, body_x + body_width, body_y + body_height], 
                    fill=cat_colors['body'], outline=cat_colors['outline'])
        
        # Голова
        head_size = body_width // 2
        head_x = body_x + body_width // 4
        head_y = body_y - head_size // 2
        draw.ellipse([head_x, head_y, head_x + head_size, head_y + head_size], 
                    fill=cat_colors['body'], outline=cat_colors['outline'])
        
        # Уши
        ear_size = head_size // 4
        # Левое ухо
        draw.polygon([(head_x + head_size//4, head_y), 
                     (head_x + head_size//4 - ear_size, head_y - ear_size),
                     (head_x + head_size//4 + ear_size, head_y - ear_size//2)], 
                    fill=cat_colors['body'], outline=cat_colors['outline'])
        # Правое ухо
        draw.polygon([(head_x + 3*head_size//4, head_y), 
                     (head_x + 3*head_size//4 - ear_size, head_y - ear_size//2),
                     (head_x + 3*head_size//4 + ear_size, head_y - ear_size)], 
                    fill=cat_colors['body'], outline=cat_colors['outline'])
        
        # Глаза
        eye_size = head_size // 8
        # Левый глаз
        draw.ellipse([head_x + head_size//4 - eye_size, head_y + head_size//3 - eye_size,
                     head_x + head_size//4 + eye_size, head_y + head_size//3 + eye_size], 
                    fill=cat_colors['eyes'])
        # Правый глаз
        draw.ellipse([head_x + 3*head_size//4 - eye_size, head_y + head_size//3 - eye_size,
                     head_x + 3*head_size//4 + eye_size, head_y + head_size//3 + eye_size], 
                    fill=cat_colors['eyes'])
        
        # Нос
        nose_size = eye_size // 2
        draw.ellipse([head_x + head_size//2 - nose_size, head_y + head_size//2 - nose_size,
                     head_x + head_size//2 + nose_size, head_y + head_size//2 + nose_size], 
                    fill='pink')
        
        # Хвост
        tail_start_x = body_x + body_width
        tail_start_y = body_y + body_height // 2
        tail_end_x = tail_start_x + body_width // 3
        tail_end_y = tail_start_y - body_height // 4
        draw.line([(tail_start_x, tail_start_y), (tail_end_x, tail_end_y)], 
                 fill=cat_colors['body'], width=body_width//6)
        
        # Лапы
        paw_size = body_width // 8
        # Передние лапы
        draw.ellipse([body_x + body_width//4 - paw_size, body_y + body_height - paw_size,
                     body_x + body_width//4 + paw_size, body_y + body_height + paw_size], 
                    fill=cat_colors['body'])
        draw.ellipse([body_x + 3*body_width//4 - paw_size, body_y + body_height - paw_size,
                     body_x + 3*body_width//4 + paw_size, body_y + body_height + paw_size], 
                    fill=cat_colors['body'])
        
        # Добавляем текст с информацией о кошке
        text = f"{cat.kitten_breed}\n{cat.colors}"
        draw.text((10, 10), text, fill='white', stroke_width=2, stroke_fill='black')
        
        return image

    def get_background_color(self, color_name):
        """Возвращает цвет фона на основе окраса кошки"""
        background_colors = {
            'Черный': '#2c3e50',
            'Белый': '#ecf0f1',
            'Серый': '#7f8c8d',
            'Рыжий': '#e67e22',
            'Трехцветный': '#8e44ad',
            'Двухцветный': '#3498db',
            'Полосатый': '#f39c12',
            'Пятнистый': '#27ae60',
            'Дымчатый': '#95a5a6',
            'Кремовый': '#f1c40f',
            'Голубой': '#3498db',
            'Шоколадный': '#8b4513',
            'Лиловый': '#9b59b6',
            'Коричневый': '#795548',
            'Золотистый': '#f39c12',
            'Серебристый': '#bdc3c7',
            'Черепаховый': '#e74c3c',
            'Калико': '#e91e63',
            'Табби': '#ff9800',
            'Сиамский окрас': '#607d8b'
        }
        return background_colors.get(color_name, '#34495e')

    def get_cat_colors(self, color_name):
        """Возвращает цвета для рисования кошки на основе окраса"""
        color_schemes = {
            'Черный': {'body': '#2c3e50', 'outline': '#1a252f', 'eyes': '#f39c12'},
            'Белый': {'body': '#ecf0f1', 'outline': '#bdc3c7', 'eyes': '#3498db'},
            'Серый': {'body': '#7f8c8d', 'outline': '#5d6d7e', 'eyes': '#f39c12'},
            'Рыжий': {'body': '#e67e22', 'outline': '#d35400', 'eyes': '#2c3e50'},
            'Трехцветный': {'body': '#8e44ad', 'outline': '#6c3483', 'eyes': '#f39c12'},
            'Двухцветный': {'body': '#3498db', 'outline': '#2980b9', 'eyes': '#f39c12'},
            'Полосатый': {'body': '#f39c12', 'outline': '#e67e22', 'eyes': '#2c3e50'},
            'Пятнистый': {'body': '#27ae60', 'outline': '#229954', 'eyes': '#f39c12'},
            'Дымчатый': {'body': '#95a5a6', 'outline': '#7f8c8d', 'eyes': '#f39c12'},
            'Кремовый': {'body': '#f1c40f', 'outline': '#f39c12', 'eyes': '#2c3e50'},
            'Голубой': {'body': '#3498db', 'outline': '#2980b9', 'eyes': '#f39c12'},
            'Шоколадный': {'body': '#8b4513', 'outline': '#654321', 'eyes': '#f39c12'},
            'Лиловый': {'body': '#9b59b6', 'outline': '#8e44ad', 'eyes': '#f39c12'},
            'Коричневый': {'body': '#795548', 'outline': '#5d4037', 'eyes': '#f39c12'},
            'Золотистый': {'body': '#f39c12', 'outline': '#e67e22', 'eyes': '#2c3e50'},
            'Серебристый': {'body': '#bdc3c7', 'outline': '#95a5a6', 'eyes': '#f39c12'},
            'Черепаховый': {'body': '#e74c3c', 'outline': '#c0392b', 'eyes': '#f39c12'},
            'Калико': {'body': '#e91e63', 'outline': '#c2185b', 'eyes': '#f39c12'},
            'Табби': {'body': '#ff9800', 'outline': '#f57c00', 'eyes': '#2c3e50'},
            'Сиамский окрас': {'body': '#607d8b', 'outline': '#455a64', 'eyes': '#f39c12'}
        }
        return color_schemes.get(color_name, {'body': '#7f8c8d', 'outline': '#5d6d7e', 'eyes': '#f39c12'}) 