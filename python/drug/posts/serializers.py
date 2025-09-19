from rest_framework import serializers
from .models import Post, Comment, PostPhoto


class PostPhotoSerializer(serializers.ModelSerializer):
    """Сериализатор для фотографий постов"""
    class Meta:
        model = PostPhoto
        fields = ['id', 'photo', 'description', 'created_at']


class CommentSerializer(serializers.ModelSerializer):
    """Сериализатор для комментариев"""
    author_name = serializers.CharField(
        source='author.profile.full_name', read_only=True)
    replies_count = serializers.SerializerMethodField()
    is_reply = serializers.ReadOnlyField()

    class Meta:
        model = Comment
        fields = [
            'id', 'body', 'author', 'author_name', 'post', 'parent',
            'likes_count', 'dislikes_count', 'replies_count', 'is_reply', 'created_at'
        ]
        read_only_fields = ['author', 'likes_count', 'dislikes_count']

    def get_replies_count(self, obj):
        return obj.replies.count()


class CommentCreateSerializer(serializers.ModelSerializer):
    """Сериализатор для создания комментариев"""
    class Meta:
        model = Comment
        fields = ['body', 'post', 'parent']

    def validate_body(self, value):
        """Валидация текста комментария"""
        if len(value.strip()) < 1:
            raise serializers.ValidationError(
                "Комментарий не может быть пустым")
        return value.strip()

    def create(self, validated_data):
        validated_data['author'] = self.context['request'].user
        return super().create(validated_data)


class PostSerializer(serializers.ModelSerializer):
    """Сериализатор для чтения постов"""
    author_full_name = serializers.CharField(
        source='author.profile.full_name', read_only=True)
    photos = PostPhotoSerializer(many=True, read_only=True)

    class Meta:
        model = Post
        fields = [
            'id', 'content', 'author', 'author_full_name',
            'likes_count', 'dislikes_count', 'comments_count',
            'photos', 'created_at', 'updated_at'
        ]
        read_only_fields = ['author', 'likes_count',
                            'dislikes_count', 'comments_count']

    def get_comments_count(self, obj):
        """Реальный подсчет комментариев"""
        return obj.comments.count()


class PostCreateSerializer(serializers.ModelSerializer):
    """Сериализатор для создания/обновления постов"""
    class Meta:
        model = Post
        fields = ('content', 'photo')

    def validate_content(self, value):
        """Валидация контента"""
        if len(value.strip()) < 1:
            raise serializers.ValidationError(
                "Содержание поста не может быть пустым")
        return value.strip()

    def create(self, validated_data):
        photos_data = validated_data.pop('photos', [])
        validated_data['author'] = self.context['request'].user
        
        post = super().create(validated_data)
        
        for photo in photos_data:
            PostPhoto.objects.create(post=post, photo=photo)
        
        return post

    def update(self, instance, validated_data):
        photos_data = validated_data.pop('photos', None)
        
        instance = super().update(instance, validated_data)
        
        if photos_data is not None:
            instance.photos.all().delete()
            for photo in photos_data:
                PostPhoto.objects.create(post=instance, photo=photo)
        
        return instance
