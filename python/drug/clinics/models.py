from django.db import models
from django.core.validators import RegexValidator
from accounts.models import User, UserProfile
from core.models import TimeStampedModel
import json


class Clinic(TimeStampedModel):
    """Ветеринарная клиника"""
    admin = models.ForeignKey(User, on_delete=models.CASCADE, related_name='owned_clinics', verbose_name='Администратор')
    name = models.CharField(max_length=200, verbose_name='Название клиники')
    license_number = models.CharField(max_length=100, unique=True, verbose_name='Номер лицензии')
    
    # Адрес и контакты
    address = models.TextField(verbose_name='Адрес')
    city = models.CharField(max_length=100, verbose_name='Город')
    latitude = models.DecimalField(max_digits=9, decimal_places=6, null=True, blank=True, verbose_name='Широта')
    longitude = models.DecimalField(max_digits=9, decimal_places=6, null=True, blank=True, verbose_name='Долгота')
    
    phone = models.CharField(max_length=20, verbose_name='Телефон')
    email = models.EmailField(verbose_name='Email')
    website = models.URLField(blank=True, verbose_name='Веб-сайт')
    
    # Рабочие часы
    working_hours = models.JSONField(default=dict, verbose_name='Часы работы')  # {"monday": "09:00-18:00"}
    
    # Дополнительная информация
    description = models.TextField(blank=True, verbose_name='Описание')
    logo = models.ImageField(upload_to='clinics/logos/', null=True, blank=True, verbose_name='Логотип')
    
    # Статус
    is_verified = models.BooleanField(default=False, verbose_name='Верифицирована')
    is_active = models.BooleanField(default=True, verbose_name='Активна')
    rating = models.DecimalField(max_digits=3, decimal_places=2, default=0, verbose_name='Рейтинг')

    class Meta:
        verbose_name = 'Клиника'
        verbose_name_plural = 'Клиники'
        ordering = ['-rating', 'name']

    def __str__(self):
        return self.name


class Veterinarian(TimeStampedModel):
    """Ветеринар"""
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='veterinarian_profile')
    profile = models.OneToOneField(UserProfile, on_delete=models.CASCADE, related_name='veterinarian_data')
    
    # Профессиональная информация
    specializations = models.ManyToManyField('Specialization', verbose_name='Специализации')
    license_number = models.CharField(max_length=100, unique=True, verbose_name='Номер лицензии')
    experience_years = models.PositiveIntegerField(verbose_name='Стаж (лет)')
    education = models.TextField(verbose_name='Образование')
    
    # Связь с клиниками
    clinics = models.ManyToManyField(Clinic, through='ClinicVeterinarian', verbose_name='Клиники')
    
    # Статус и рейтинг
    is_active = models.BooleanField(default=True, verbose_name='Активен')
    rating = models.DecimalField(max_digits=3, decimal_places=2, default=0, verbose_name='Рейтинг')
    consultation_price = models.DecimalField(max_digits=8, decimal_places=2, null=True, blank=True, verbose_name='Стоимость консультации')

    class Meta:
        verbose_name = 'Ветеринар'
        verbose_name_plural = 'Ветеринары'

    def __str__(self):
        return f"Доктор {self.profile.full_name}"


class Specialization(TimeStampedModel):
    """Специализации ветеринаров"""
    name = models.CharField(max_length=100, unique=True, verbose_name='Название')
    description = models.TextField(blank=True, verbose_name='Описание')

    class Meta:
        verbose_name = 'Специализация'
        verbose_name_plural = 'Специализации'

    def __str__(self):
        return self.name


class ClinicVeterinarian(TimeStampedModel):
    """Связь ветеринара с клиникой"""
    clinic = models.ForeignKey(Clinic, on_delete=models.CASCADE)
    veterinarian = models.ForeignKey(Veterinarian, on_delete=models.CASCADE)
    position = models.CharField(max_length=100, verbose_name='Должность')
    is_primary = models.BooleanField(default=False, verbose_name='Основное место работы')
    start_date = models.DateField(verbose_name='Дата начала работы')
    end_date = models.DateField(null=True, blank=True, verbose_name='Дата окончания работы')

    class Meta:
        verbose_name = 'Ветеринар клиники'
        verbose_name_plural = 'Ветеринары клиник'
        unique_together = ('clinic', 'veterinarian')


class Service(TimeStampedModel):
    """Услуги клиники"""
    clinic = models.ForeignKey(Clinic, on_delete=models.CASCADE, related_name='services')
    name = models.CharField(max_length=200, verbose_name='Название услуги')
    description = models.TextField(blank=True, verbose_name='Описание')
    price = models.DecimalField(max_digits=8, decimal_places=2, verbose_name='Цена')
    duration_minutes = models.PositiveIntegerField(verbose_name='Длительность (мин)')
    category = models.ForeignKey('ServiceCategory', on_delete=models.CASCADE, verbose_name='Категория')
    is_active = models.BooleanField(default=True, verbose_name='Активна')

    class Meta:
        verbose_name = 'Услуга'
        verbose_name_plural = 'Услуги'

    def __str__(self):
        return f"{self.clinic.name} - {self.name}"


class ServiceCategory(TimeStampedModel):
    """Категории услуг"""
    name = models.CharField(max_length=100, unique=True, verbose_name='Название')
    description = models.TextField(blank=True, verbose_name='Описание')
    icon = models.CharField(max_length=50, blank=True, verbose_name='Иконка')

    class Meta:
        verbose_name = 'Категория услуг'
        verbose_name_plural = 'Категории услуг'

    def __str__(self):
        return self.name