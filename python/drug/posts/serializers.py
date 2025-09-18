from rest_framework import serializers
from .models import Post, Comment, PostPhoto


class PostSerializer(serializers.ModelSerializer):
    author_name = serializers.CharField(
        source='user.profile.full_name', read_only=True)

    class Meta:
        model = Post
        fields = ('__all__', 'author_name')  # ?


class PostCreateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Post
        fields = ('author', 'content', 'photo')

    def create(self, validated_data):
        validated_data['author'] = self.context['request'].user
        return super().create(validated_data)