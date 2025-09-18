from django.db import models
from django.core.validators import MinValueValidator, MaxValueValidator
from accounts.models import User
from clinics.models import Clinic, Veterinarian
from core.mixins import TimeStampedMixin


class Review(TimeStampedMixin):
    """Отзывы о клиниках и ветеринарах"""
    REVIEW_TYPES = [
        ('clinic', 'Отзыв о клинике'),
        ('veterinarian', 'Отзыв о ветеринаре'),
    ]

    author = models.ForeignKey(User, on_delete=models.CASCADE, related_name='reviews')
    review_type = models.CharField(max_length=20, choices=REVIEW_TYPES)
    
    # Объект отзыва (через Generic Foreign Key можно сделать более универсально)
    clinic = models.ForeignKey(Clinic, on_delete=models.CASCADE, null=True, blank=True, related_name='reviews')
    veterinarian = models.ForeignKey(Veterinarian, on_delete=models.CASCADE, null=True, blank=True, related_name='reviews')
    
    # Содержание отзыва
    rating = models.PositiveIntegerField(
        validators=[MinValueValidator(1), MaxValueValidator(5)],
        verbose_name='Оценка'
    )
    title = models.CharField(max_length=200, verbose_name='Заголовок')
    content = models.TextField(verbose_name='Текст отзыва')
    
    # Модерация
    is_approved = models.BooleanField(default=False, verbose_name='Одобрен')
    is_anonymous = models.BooleanField(default=False, verbose_name='Анонимный')

    class Meta:
        verbose_name = 'Отзыв'
        verbose_name_plural = 'Отзывы'
        ordering = ['-created_at']

    def __str__(self):
        target = self.clinic or self.veterinarian
        return f"Отзыв о {target} - {self.rating}/5"