from django.db import models
from django.core.validators import MinValueValidator, MaxValueValidator


class TimeStampedMixin(models.Model):
    """Миксин для временных меток"""
    created_at = models.DateTimeField(
        auto_now_add=True, verbose_name='Дата создания')
    updated_at = models.DateTimeField(
        auto_now=True, verbose_name='Дата обновления')

    class Meta:
        abstract = True


class LikeMixin(models.Model):
    """Миксин для системы лайков"""
    liked_by = models.ManyToManyField(
        'accounts.User',
        blank=True,
        related_name="liked_%(class)s",
        verbose_name="Лайки пользователей"
    )
    disliked_by = models.ManyToManyField(
        'accounts.User',
        blank=True,
        related_name="disliked_%(class)s",
        verbose_name="Дизлайки пользователей"
    )
    likes_count = models.PositiveIntegerField(
        default=0, verbose_name='Количество лайков')
    dislikes_count = models.PositiveIntegerField(
        default=0, verbose_name='Количество дизлайков')

    class Meta:
        abstract = True

    def toggle_like(self, user):
        """Поставить/убрать лайк"""
        if self.liked_by.filter(id=user.id).exists():
            self.liked_by.remove(user)
            self.likes_count = max(0, self.likes_count - 1)
        else:
            self.liked_by.add(user)
            self.likes_count += 1
        self.save(update_fields=['likes_count'])

    def toggle_dislike(self, user):
        """Поставить/убрать дизлайк"""
        if self.disliked_by.filter(id=user.id).exists():
            self.disliked_by.remove(user)
            self.dislikes_count = max(0, self.dislikes_count - 1)
        else:
            if self.liked_by.filter(id=user.id).exists():
                self.liked_by.remove(user)
                self.likes_count = max(0, self.likes_count - 1)
            self.disliked_by.add(user)
            self.likes_count += 1
        self.save(update_fields=['dislikes_count'])

    @property
    def dislikes_count_actual(self):
        return self.disliked_by.count()

    @property
    def likes_count_actual(self):
        return self.liked_by.count()


class RatingMixin(models.Model):
    """Миксин для рейтинговой системы"""
    rating = models.PositiveIntegerField(
        validators=[MinValueValidator(1), MaxValueValidator(5)],
        verbose_name='Рейтинг'
    )

    class Meta:
        abstract = True

    def get_stars_display(self):
        """Получить рейтинг в виде звездочек"""
        return "⭐" * self.rating + "☆" * (5 - self.rating)


class SoftDeleteMixin(models.Model):
    """Миксин для мягкого удаления"""
    is_deleted = models.BooleanField(default=False, verbose_name='Удален')
    deleted_at = models.DateTimeField(
        null=True, blank=True, verbose_name='Дата удаления')

    class Meta:
        abstract = True

    def soft_delete(self):
        """Мягкое удаление объекта"""
        from django.utils import timezone
        self.is_deleted = True
        self.deleted_at = timezone.now()
        self.save(update_fields=['is_deleted', 'deleted_at'])

    def restore(self):
        """Восстановить удаленный объект"""
        self.is_deleted = False
        self.deleted_at = None
        self.save(update_fields=['is_deleted', 'deleted_at'])
