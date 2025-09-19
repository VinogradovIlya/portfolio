from rest_framework.decorators import api_view, permission_classes
from rest_framework import permissions, status
from rest_framework.response import Response
from django.shortcuts import get_object_or_404
from .models import Post, Comment
from .serializers import (
    PostSerializer, PostCreateSerializer,
    CommentSerializer, CommentCreateSerializer
)


@api_view(['GET', 'POST'])
@permission_classes([permissions.IsAuthenticated])
def posts_list(request):
    """
    GET: Получить все посты (лента)
    POST: Создать новый пост
    """
    if request.method == 'GET':
        posts = Post.objects.all().select_related('author').prefetch_related('photos')
        serializer = PostSerializer(posts, many=True)
        return Response(serializer.data)

    elif request.method == 'POST':
        serializer = PostCreateSerializer(data=request.data, context={'request': request})
        if serializer.is_valid():
            post = serializer.save()
            return Response(PostSerializer(post).data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@api_view(['GET', 'PUT', 'DELETE'])
@permission_classes([permissions.IsAuthenticated])
def post_detail(request, post_id):
    """
    GET: Получить конкретный пост
    PUT: Обновить пост (только автор)
    DELETE: Удалить пост (только автор)
    """
    post = get_object_or_404(Post, id=post_id)

    if request.method == 'GET':
        serializer = PostSerializer(post)
        return Response(serializer.data)

    elif request.method in ['PUT', 'DELETE']:
        if post.author != request.user:
            return Response(
                {'error': 'Вы можете редактировать только свои посты'},
                status=status.HTTP_403_FORBIDDEN
            )

        if request.method == 'PUT':
            serializer = PostCreateSerializer(post, data=request.data, partial=True)
            if serializer.is_valid():
                post = serializer.save()
                return Response(PostSerializer(post).data)
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        elif request.method == 'DELETE':
            post.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)


@api_view(['POST'])
@permission_classes([permissions.IsAuthenticated])
def post_like(request, post_id):
    """Лайкнуть пост"""
    post = get_object_or_404(Post, id=post_id)
    post.toggle_like(request.user)
    return Response({
        'likes_count': post.likes_count,
        'dislikes_count': post.dislikes_count
    })


@api_view(['POST'])
@permission_classes([permissions.IsAuthenticated])
def post_dislike(request, post_id):
    """Дизлайкнуть пост"""
    post = get_object_or_404(Post, id=post_id)
    post.toggle_dislike(request.user)
    return Response({
        'likes_count': post.likes_count,
        'dislikes_count': post.dislikes_count
    })


@api_view(['GET', 'POST'])
@permission_classes([permissions.IsAuthenticated])
def post_comments(request, post_id):
    """
    GET: Получить комментарии к посту
    POST: Добавить комментарий к посту
    """
    post = get_object_or_404(Post, id=post_id)

    if request.method == 'GET':
        # Получаем только основные комментарии (не ответы)
        comments = post.comments.filter(parent=None).select_related('author')
        serializer = CommentSerializer(comments, many=True)
        return Response(serializer.data)

    elif request.method == 'POST':
        data = request.data.copy()
        data['post'] = post.id

        serializer = CommentCreateSerializer(data=data, context={'request': request})
        if serializer.is_valid():
            comment = serializer.save()
            return Response(CommentSerializer(comment).data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@api_view(['GET'])
@permission_classes([permissions.IsAuthenticated])
def comment_replies(request, comment_id):
    """Получить ответы на комментарий"""
    comment = get_object_or_404(Comment, id=comment_id)
    replies = comment.get_replies()
    serializer = CommentSerializer(replies, many=True)
    return Response(serializer.data)


@api_view(['GET'])
@permission_classes([permissions.IsAuthenticated])
def user_posts(request, user_id):
    """Получить посты конкретного пользователя"""
    posts = Post.objects.filter(author_id=user_id).select_related('author').prefetch_related('photos')
    serializer = PostSerializer(posts, many=True)
    return Response(serializer.data)