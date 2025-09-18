from django.db import models
from django.contrib.contenttypes.models import ContentType
from django.contrib.contenttypes.fields import GenericForeignKey
from accounts.models import User
from core.mixins import TimeStampedMixin


class Conversation(TimeStampedMixin):
    """Диалоги между пользователями"""
    CONVERSATION_TYPES = [
        ('private', 'Личная переписка'),
        ('support', 'Техподдержка'),
        ('business', 'Бизнес переписка'),
        ('group', 'Групповой чат'),
    ]

    participants = models.ManyToManyField(User, through='ConversationParticipant', verbose_name='Участники')
    conversation_type = models.CharField(max_length=20, choices=CONVERSATION_TYPES, default='private', verbose_name='Тип диалога')
    subject = models.CharField(max_length=200, blank=True, verbose_name='Тема')
    is_active = models.BooleanField(default=True, verbose_name='Активен')
    
    # Связанный объект (заказ, питомец, запись на прием и т.д.)
    related_content_type = models.ForeignKey(ContentType, on_delete=models.CASCADE, null=True, blank=True)
    related_object_id = models.PositiveIntegerField(null=True, blank=True)
    related_object = GenericForeignKey('related_content_type', 'related_object_id')

    class Meta:
        verbose_name = 'Диалог'
        verbose_name_plural = 'Диалоги'
        ordering = ['-updated_at']

    @property
    def last_message(self):
        return self.messages.first()

    def __str__(self):
        participant_names = [p.email for p in self.participants.all()[:2]]
        return f"Диалог: {' - '.join(participant_names)}"


class ConversationParticipant(TimeStampedMixin):
    """Участники диалога"""
    conversation = models.ForeignKey(Conversation, on_delete=models.CASCADE, verbose_name='Диалог')
    user = models.ForeignKey(User, on_delete=models.CASCADE, verbose_name='Пользователь')
    joined_at = models.DateTimeField(auto_now_add=True, verbose_name='Дата присоединения')
    left_at = models.DateTimeField(null=True, blank=True, verbose_name='Дата выхода')
    last_read_at = models.DateTimeField(null=True, blank=True, verbose_name='Последнее прочтение')
    is_muted = models.BooleanField(default=False, verbose_name='Уведомления отключены')

    class Meta:
        verbose_name = 'Участник диалога'
        verbose_name_plural = 'Участники диалогов'
        unique_together = ('conversation', 'user')

    def __str__(self):
        return f"{self.user.email} в {self.conversation}"


class Message(TimeStampedMixin):
    """Сообщения"""
    MESSAGE_TYPES = [
        ('text', 'Текстовое сообщение'),
        ('image', 'Изображение'),
        ('file', 'Файл'),
        ('system', 'Системное сообщение'),
    ]

    conversation = models.ForeignKey(Conversation, on_delete=models.CASCADE, related_name='messages', verbose_name='Диалог')
    sender = models.ForeignKey(User, on_delete=models.CASCADE, related_name='sent_messages', verbose_name='Отправитель')
    
    message_type = models.CharField(max_length=20, choices=MESSAGE_TYPES, default='text', verbose_name='Тип сообщения')
    content = models.TextField(verbose_name='Содержимое')
    
    # Ответ на сообщение
    reply_to = models.ForeignKey('self', on_delete=models.CASCADE, null=True, blank=True, related_name='replies', verbose_name='Ответ на')
    
    # Статус сообщения
    is_edited = models.BooleanField(default=False, verbose_name='Отредактировано')
    edited_at = models.DateTimeField(null=True, blank=True, verbose_name='Время редактирования')
    is_deleted = models.BooleanField(default=False, verbose_name='Удалено')

    class Meta:
        verbose_name = 'Сообщение'
        verbose_name_plural = 'Сообщения'
        ordering = ['-created_at']

    def __str__(self):
        return f"Сообщение от {self.sender.email} в {self.conversation}"


class MessageAttachment(TimeStampedMixin):
    """Вложения в сообщениях"""
    message = models.ForeignKey(Message, on_delete=models.CASCADE, related_name='attachments', verbose_name='Сообщение')
    file_name = models.CharField(max_length=255, verbose_name='Имя файла')
    file_size = models.PositiveIntegerField(verbose_name='Размер файла (байты)')
    file_type = models.CharField(max_length=50, verbose_name='Тип файла')

    class Meta:
        verbose_name = 'Вложение'
        verbose_name_plural = 'Вложения'

    def __str__(self):
        return f"Вложение: {self.file_name}"


class MessageRead(TimeStampedMixin):
    """Прочтение сообщений"""
    message = models.ForeignKey(Message, on_delete=models.CASCADE, related_name='read_by', verbose_name='Сообщение')
    user = models.ForeignKey(User, on_delete=models.CASCADE, verbose_name='Пользователь')
    read_at = models.DateTimeField(auto_now_add=True, verbose_name='Время прочтения')

    class Meta:
        verbose_name = 'Прочтение сообщения'
        verbose_name_plural = 'Прочтения сообщений'
        unique_together = ('message', 'user')

    def __str__(self):
        return f"{self.user.email} прочитал сообщение {self.message.id}"