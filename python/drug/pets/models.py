from django.db import models
from accounts.models import User
from core.models import TimeStampedModel


class Breed(TimeStampedModel):
    """Породы животных"""
    SPECIES_CHOICES = [
        ('cat', 'Кошка'),
        ('dog', 'Собака'),
        ('bird', 'Птица'),
        ('fish', 'Рыба'),
        ('rodent', 'Грызун'),
        ('reptile', 'Рептилия'),
        ('other', 'Другое'),
    ]
    
    name = models.CharField(max_length=100, verbose_name='Название породы')
    species = models.CharField(max_length=20, choices=SPECIES_CHOICES, verbose_name='Вид животного')
    description = models.TextField(blank=True, verbose_name='Описание')

    class Meta:
        verbose_name = 'Порода'
        verbose_name_plural = 'Породы'
        unique_together = ('name', 'species')

    def __str__(self):
        return f"{self.get_species_display()} - {self.name}"


class Pet(TimeStampedModel):
    """Питомец"""
    COLORS = [
        ('white', 'Белый'),
        ('black', 'Черный'),
        ('grey', 'Серый'),
        ('brown', 'Коричневый'),
        ('red', 'Рыжий'),
        ('multi', 'Разноцветный'),
        ('other', 'Другой'),
    ]
    GENDERS = [
        ('m', 'Мужской'),
        ('f', 'Женский'),
        ('unknown', 'Не известно'),
    ]

    owner = models.ForeignKey(User, on_delete=models.CASCADE, related_name='pets', verbose_name='Владелец')
    name = models.CharField(max_length=50, verbose_name='Кличка')
    breed = models.ForeignKey(Breed, on_delete=models.CASCADE, verbose_name='Порода')
    birthday = models.DateField(verbose_name='Дата рождения')
    gender = models.CharField(max_length=10, choices=GENDERS, default='unknown', verbose_name='Пол')
    color = models.CharField(max_length=20, choices=COLORS, verbose_name='Окрас')
    weight = models.DecimalField(max_digits=6, decimal_places=2, null=True, blank=True, verbose_name='Вес (кг)')
    
    passport_number = models.CharField(max_length=20, unique=True, null=True, blank=True, verbose_name='Номер паспорта')
    is_chipped = models.BooleanField(default=False, verbose_name='Чипирован')
    chip_number = models.CharField(max_length=50, unique=True, null=True, blank=True, verbose_name='Номер чипа')
    
    description = models.TextField(blank=True, verbose_name='Описание')
    special_needs = models.TextField(blank=True, verbose_name='Особые потребности')
    is_active = models.BooleanField(default=True, verbose_name='Активен') #?
    
    main_photo = models.ImageField(upload_to='pets/main/', null=True, blank=True, verbose_name='Основное фото')

    class Meta:
        verbose_name = 'Питомец'
        verbose_name_plural = 'Питомцы'
        ordering = ['-created_at']

    def __str__(self):
        return f"{self.name} ({self.breed.name})"

    @property
    def age_in_years(self):
        from datetime import date
        today = date.today()
        return today.year - self.birthday.year - ((today.month, today.day) < (self.birthday.month, self.birthday.day))


class PetPhoto(TimeStampedModel):
    """Дополнительные фотографии питомца"""
    pet = models.ForeignKey(Pet, on_delete=models.CASCADE, related_name='photos')
    photo = models.ImageField(upload_to='pets/photos/')
    description = models.CharField(max_length=200, blank=True, verbose_name='Описание')

    class Meta:
        verbose_name = 'Фото питомца'
        verbose_name_plural = 'Фото питомцев'