from django.db import models


class TimeStampedModel(models.Model):
    """Абстрактная модель с полями времени создания и обновления"""
    created_at = models.DateTimeField(
        auto_now_add=True, verbose_name='Дата создания')
    updated_at = models.DateTimeField(
        auto_now=True, verbose_name='Дата обновления')

    class Meta:
        abstract = True
