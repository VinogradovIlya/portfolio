from django.db import models
from core.mixins import LikeMixin, TimeStampedMixin
from accounts.models import User


class Post(TimeStampedMixin, LikeMixin):
    """Посты для новостной ленты"""
    author = models.ForeignKey(
        User, on_delete=models.CASCADE, related_name='posts', verbose_name='Посты')
    content = models.CharField(
        max_length=200, verbose_name='Описание', blank=True)

    comment_by = models.ManyToManyField(
        User, blank=True, related_name='commented_posts')

    comments_count = models.PositiveIntegerField(default=0)

    class Meta:
        verbose_name = 'Пост'
        verbose_name_plural = 'Посты'
        ordering = ['-created_at']
        indexes = [
            models.Index(fields=['author', '-created_at']),
        ]

    def __str__(self):
        return f'{self.author.email}: {self.content[:50]}...'

    @property
    def comments_count_actual(self):
        return self.comment_by.count()


class Comment(TimeStampedMixin, LikeMixin):
    """Комментарии к постам"""
    author = models.ForeignKey(
        User, on_delete=models.CASCADE, related_name='comments')
    post = models.ForeignKey(
        Post, on_delete=models.CASCADE, related_name='comments')
    body = models.TextField(verbose_name='Текст комментария')

    parent = models.ForeignKey(
        'self', on_delete=models.CASCADE, null=True, blank=True, related_name='replies')

    class Meta:
        verbose_name = 'Комментарий'
        verbose_name_plural = 'Комментарии'
        ordering = ['-likes_count', '-created_at']

        indexes = [
            models.Index(fields=['post', '-likes_count', '-created_at']),
            models.Index(fields=['parent']),
        ]

    def __str__(self):
        return f'{self.author.email}: {self.body[:50]}...'

    @property
    def is_reply(self):
        """Проверяет, является ли это ответом на другой комментарий"""
        return self.parent is not None

    def get_replies(self):
        """Получить все ответы на этот комментарий"""
        return self.replies.all().order_by('-likes_count', '-created_at')


class PostPhoto(TimeStampedMixin, LikeMixin):
    """Дополнительные фото к постам"""
    post = models.ForeignKey(
        Post, on_delete=models.CASCADE, related_name='photos')
    photo = models.ImageField(upload_to='posts/photos/')

    class Meta:
        verbose_name = 'Фото к посту'
        verbose_name_plural = 'Фото к постам'
        ordering = ['created_at']


class PostLike(TimeStampedMixin):
    """Лайки постов"""
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    post = models.ForeignKey(Post, on_delete=models.CASCADE)

    class Meta:
        unique_together = ('user', 'post')
        verbose_name = 'Лайк поста'
        verbose_name_plural = 'Лайки постов'
