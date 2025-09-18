from django.contrib.auth.models import AbstractUser, UserManager
from django.db import models
from phonenumber_field.modelfields import PhoneNumberField
from core.mixins import TimeStampedMixin


class CustomUserManager(UserManager):
    def create_user(self, email, password=None, **extra_fields):
        if not email:
            raise ValueError('Email is required')

        email = self.normalize_email(email)
        user = self.model(email=email, **extra_fields)
        user.set_password(password)
        user.save(using=self._db)

        UserProfile.objects.create(
            user=user,
            first_name='',
            last_name=''
        )
        return user

    def create_superuser(self, email, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)
        extra_fields.setdefault('user_type', 'admin')
        return self.create_user(email, password, **extra_fields)


class User(AbstractUser, TimeStampedMixin):
    USER_TYPE_CHOICES = [
        ('pet_owner', 'Владелец питомца'),
        ('veterinarian', 'Ветеринар'),
        ('clinic_admin', 'Администратор клиники'),
        ('business', 'Бизнес'),
        ('admin', 'Администратор'),
    ]

    username = None
    email = models.EmailField(unique=True, verbose_name='Email')
    user_type = models.CharField(max_length=20, choices=USER_TYPE_CHOICES,
                                 verbose_name='Тип пользователя', default=USER_TYPE_CHOICES[0][0])
    phone = PhoneNumberField(unique=True, region='RU', verbose_name='Телефон')
    city = models.CharField(max_length=100, verbose_name='Город')

    is_verified = models.BooleanField(
        default=False, verbose_name='Верифицирован')
    is_active = models.BooleanField(default=True, verbose_name='Активен')
    subscriber = models.BooleanField(default=False, verbose_name='Подписчик')
    last_seen = models.DateTimeField(
        null=True, blank=True, verbose_name='Последняя активность')

    objects = CustomUserManager()

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = []

    class Meta:
        verbose_name = 'Пользователь'
        verbose_name_plural = 'Пользователи'

    def __str__(self):
        return f"{self.email} ({self.get_user_type_display()})"


class UserProfile(TimeStampedMixin):
    """Базовый профиль для всех пользователей с личными данными"""
    GENDERS = [
        ('m', 'Мужской'),
        ('f', 'Женский'),
        ('unknown', 'Не указано'),
    ]

    user = models.OneToOneField(
        User, on_delete=models.CASCADE, related_name='profile')
    first_name = models.CharField(max_length=50, verbose_name='Имя')
    last_name = models.CharField(max_length=50, verbose_name='Фамилия')
    middle_name = models.CharField(
        max_length=50, blank=True, null=True, verbose_name='Отчество')
    birthday = models.DateField(
        null=True, blank=True, verbose_name='Дата рождения')
    gender = models.CharField(
        max_length=10, choices=GENDERS, default='unknown', verbose_name='Пол')
    avatar = models.ImageField(
        upload_to='avatars/', null=True, blank=True, verbose_name='Аватар')
    bio = models.TextField(max_length=500, blank=True, verbose_name='О себе')

    class Meta:
        verbose_name = 'Профиль пользователя'
        verbose_name_plural = 'Профили пользователей'

    def __str__(self):
        return f"{self.first_name} {self.last_name}"

    @property
    def full_name(self):
        parts = [self.first_name, self.middle_name, self.last_name]
        return ' '.join(filter(None, parts))
