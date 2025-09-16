from drf_spectacular.utils import extend_schema, OpenApiResponse, OpenApiExample
from rest_framework import status, permissions
from rest_framework.decorators import api_view, permission_classes
from rest_framework.response import Response
from rest_framework.authtoken.models import Token
from django.utils import timezone
from .serializers import UserRegistrationSerializer, UserLoginSerializer, UserSerializer, PasswordRecoverySerializer


@api_view(['PUT'])
@permission_classes([permissions.AllowAny])
def recovery_view(request):
    """Восстановление пароля"""
    serialiser = PasswordRecoverySerializer(data=request.data)

    if serialiser.is_valid():
        user = serialiser.save()
        token, created = Token.objects.get(user=user)


@extend_schema(
    operation_id='user_register',
    tags=['Authentication'],
    summary='Регистрация нового пользователя',
    description='Создание нового аккаунта пользователя с email и паролем',
    request=UserRegistrationSerializer,
    responses={
        201: OpenApiResponse(
            response=UserSerializer,
            description='Пользователь успешно зарегистрирован',
            examples=[
                OpenApiExample(
                    'Успешная регистрация',
                    value={
                        'message': 'Пользователь успешно зарегистрирован',
                        'user': {
                            'id': 1,
                            'email': 'user@example.com',
                            'user_type': 'pet_owner'
                        },
                        'token': 'abcd1234token'
                    }
                )
            ]
        ),
        400: OpenApiResponse(description='Ошибки валидации')
    }
)
@api_view(['POST'])
@permission_classes([permissions.AllowAny])
def register_view(request):
    """Регистрация нового пользователя"""
    serializer = UserRegistrationSerializer(data=request.data)

    if serializer.is_valid():
        user = serializer.save()
        token, created = Token.objects.get_or_create(user=user)

        return Response({
            'message': 'Пользователь успешно зарегистрирован',
            'user': UserSerializer(user).data,
            'token': token.key
        }, status=status.HTTP_201_CREATED)

    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@extend_schema(
    operation_id='user_login',
    tags=['Authentication'],
    summary='Авторизация пользователя',
    description='Вход в систему с получением токена аутентификации',
    request=UserLoginSerializer,
    responses={
        200: OpenApiResponse(response=UserSerializer, description='Успешная авторизация'),
        400: OpenApiResponse(description='Неверные данные для входа')
    }
)
@api_view(['POST'])
@permission_classes([permissions.AllowAny])
def login_view(request):
    """Авторизация пользователя"""
    serializer = UserLoginSerializer(data=request.data)

    if serializer.is_valid():
        user = serializer.validated_data['user']
        token, created = Token.objects.get_or_create(user=user)

        user.last_seen = timezone.now()
        user.save(update_fields=['last_seen'])

        return Response({
            'message': 'Успешная авторизация',
            'user': UserSerializer(user).data,
            'token': token.key
        })

    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@api_view(['POST'])
@permission_classes([permissions.IsAuthenticated])
def logout_view(request):
    """Выход из системы"""
    try:
        request.user.auth_token.delete()
        return Response({'message': 'Вы успешно вышли из системы'})
    except:
        return Response({'error': 'Ошибка при выходе'}, status=status.HTTP_400_BAD_REQUEST)


@api_view(['GET', 'PUT'])
@permission_classes([permissions.IsAuthenticated])
def profile_view(request):
    """
    GET: Получение профиля текущего пользователя
    PUT: Обновить профиль пользователя
    """

    if request.method == 'GET':
        serializer = UserSerializer(request.user)
        return Response(serializer.data)
    elif request.method == 'PUT':
        serializer = UserSerializer(
            request.user, 
            data=request.data, 
            partial=True
        )
        
        if serializer.is_valid():
            user = serializer.save()
            return Response(UserSerializer(user).data)
        
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

