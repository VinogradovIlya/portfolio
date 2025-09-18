from django.db import models
from accounts.models import User
from core.mixins import TimeStampedMixin


class Notification(TimeStampedMixin):
    """Уведомления пользователей"""
    NOTIFICATION_TYPES = [
        ('appointment_reminder', 'Напоминание о записи'),
        ('appointment_confirmed', 'Запись подтверждена'),
        ('appointment_cancelled', 'Запись отменена'),
        ('vaccination_due', 'Пора делать прививку'),
        ('new_message', 'Новое сообщение'),
        ('system', 'Системное уведомление'),
    ]

    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name='notifications')
    title = models.CharField(max_length=200, verbose_name='Заголовок')
    message = models.TextField(verbose_name='Сообщение')
    notification_type = models.CharField(max_length=30, choices=NOTIFICATION_TYPES)
    
    is_read = models.BooleanField(default=False, verbose_name='Прочитано')
    is_sent = models.BooleanField(default=False, verbose_name='Отправлено')
    
    # Дополнительные данные (JSON)
    extra_data = models.JSONField(default=dict, blank=True)
    
    # Каналы доставки
    send_push = models.BooleanField(default=True, verbose_name='Push уведомление')
    send_email = models.BooleanField(default=False, verbose_name='Email уведомление')
    send_sms = models.BooleanField(default=False, verbose_name='SMS уведомление')

    class Meta:
        verbose_name = 'Уведомление'
        verbose_name_plural = 'Уведомления'
        ordering = ['-created_at']

    def __str__(self):
        return f"{self.user.email} - {self.title}"