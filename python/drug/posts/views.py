from rest_framework.decorators import api_view, permission_classes
from rest_framework import permissions, status
from rest_framework.response import Response
from .models import Post
from .serializers import PostSerializer, PostCreateSerializer


@api_view(['GET'])
@permission_classes([permissions.IsAuthenticatedOrReadOnly])
def posts_list(request):
    # нежно добавить пагинацию
    """
    GET: Получить все посты
    """
    if request.method == 'GET':
        news = Post.objects.all()
        serializer = PostSerializer()
        return Response(serializer.data)


@api_view(['GET', 'POST', 'PUT', 'DELETE'])
@permission_classes([permissions.IsAuthenticated])
def user_posts(request, user_id):
    """
    GET: Получить все посты конкретного пользователя
    POST: Создать пост от конкретного пользователя
    PUT: Обновить пост конкретного пользователя
    DELETE: Удалить пост конкретного пользователя
    """
    try:
        # post = Post.objects.get(id=user_id, author=request.user)
        post = Post.objects.get(author=request.user)
    except Post.DoesNotExist:
        return Response(
            {'error': 'У вас пока нет постов'},
            status=status.HTTP_404_NOT_FOUND)

    if request.method == 'GET':
        serializer = PostSerializer(post)
        return Response(serializer.data)

    elif request.method == 'POST':
        serializer = PostCreateSerializer(
            data=request.data, context={'request': request})
        if serializer.is_valid():
            post = serializer.save()
            return Response(PostCreateSerializer(post).data,
                            status=status.HTTP_201_CREATED)
    
    elif request.method == 'PUT':
        serializer = PostCreateSerializer(post, data=request.data, partial=True)
        if serializer.is_valid():
            post = serializer.save()
            return Response(PostSerializer(post).data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    elif request.method == 'DELETE':
        post.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)
