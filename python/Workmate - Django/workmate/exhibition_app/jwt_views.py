from rest_framework import status
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import AllowAny
from rest_framework.response import Response
from rest_framework_simplejwt.tokens import RefreshToken
from django.contrib.auth import authenticate
from django.contrib.auth.models import User
from .serializers import KittenOwnerSerializer
from .models import KittenOwner

@api_view(['POST'])
@permission_classes([AllowAny])
def register(request):
    """
    Регистрация нового пользователя
    """
    try:
        # Создаем Django User
        username = request.data.get('username')
        email = request.data.get('email')
        password = request.data.get('password')
        
        if not all([username, email, password]):
            return Response({
                'error': 'Необходимо указать username, email и password'
            }, status=status.HTTP_400_BAD_REQUEST)
        
        if User.objects.filter(username=username).exists():
            return Response({
                'error': 'Пользователь с таким username уже существует'
            }, status=status.HTTP_400_BAD_REQUEST)
        
        if User.objects.filter(email=email).exists():
            return Response({
                'error': 'Пользователь с таким email уже существует'
            }, status=status.HTTP_400_BAD_REQUEST)
        
        # Создаем пользователя
        user = User.objects.create_user(
            username=username,
            email=email,
            password=password
        )
        
        # Создаем профиль владельца кошки
        owner_data = {
            'name': request.data.get('name', ''),
            'surname': request.data.get('surname', ''),
            'patronymic': request.data.get('patronymic', '')
        }
        
        owner_serializer = KittenOwnerSerializer(data=owner_data)
        if owner_serializer.is_valid():
            owner = owner_serializer.save()
            
            # Генерируем JWT токены
            refresh = RefreshToken.for_user(user)
            
            return Response({
                'message': 'Пользователь успешно зарегистрирован',
                'user': {
                    'id': user.id,
                    'username': user.username,
                    'email': user.email
                },
                'owner': owner_serializer.data,
                'tokens': {
                    'refresh': str(refresh),
                    'access': str(refresh.access_token),
                }
            }, status=status.HTTP_201_CREATED)
        else:
            user.delete()
            return Response({
                'error': 'Ошибка в данных владельца',
                'details': owner_serializer.errors
            }, status=status.HTTP_400_BAD_REQUEST)
            
    except Exception as e:
        return Response({
            'error': f'Ошибка при регистрации: {str(e)}'
        }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

@api_view(['POST'])
@permission_classes([AllowAny])
def login(request):
    """
    Авторизация пользователя
    """
    try:
        username = request.data.get('username')
        password = request.data.get('password')
        
        if not all([username, password]):
            return Response({
                'error': 'Необходимо указать username и password'
            }, status=status.HTTP_400_BAD_REQUEST)
        
        # Аутентификация пользователя
        user = authenticate(username=username, password=password)
        
        if user is None:
            return Response({
                'error': 'Неверные учетные данные'
            }, status=status.HTTP_401_UNAUTHORIZED)
        
        # Генерируем JWT токены
        refresh = RefreshToken.for_user(user)
        
        # Получаем профиль владельца
        try:
            owner = KittenOwner.objects.get(
                name=user.first_name or user.username,
                surname=user.last_name or ''
            )
            owner_serializer = KittenOwnerSerializer(owner)
            owner_data = owner_serializer.data
        except KittenOwner.DoesNotExist:
            owner_data = None
        
        return Response({
            'message': 'Успешная авторизация',
            'user': {
                'id': user.id,
                'username': user.username,
                'email': user.email
            },
            'owner': owner_data,
            'tokens': {
                'refresh': str(refresh),
                'access': str(refresh.access_token),
            }
        }, status=status.HTTP_200_OK)
        
    except Exception as e:
        return Response({
            'error': f'Ошибка при авторизации: {str(e)}'
        }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

@api_view(['POST'])
def logout(request):
    """
    Выход пользователя (блокировка токена)
    """
    try:
        refresh_token = request.data.get('refresh_token')
        
        if not refresh_token:
            return Response({
                'error': 'Необходимо указать refresh_token'
            }, status=status.HTTP_400_BAD_REQUEST)
        
        # Блокируем refresh токен
        token = RefreshToken(refresh_token)
        token.blacklist()
        
        return Response({
            'message': 'Успешный выход из системы'
        }, status=status.HTTP_200_OK)
        
    except Exception as e:
        return Response({
            'error': f'Ошибка при выходе: {str(e)}'
        }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

@api_view(['GET'])
def profile(request):
    """
    Получить профиль текущего пользователя
    """
    try:
        user = request.user
        
        if not user.is_authenticated:
            return Response({
                'error': 'Пользователь не авторизован'
            }, status=status.HTTP_401_UNAUTHORIZED)
        
        # Получаем профиль владельца
        try:
            owner = KittenOwner.objects.get(
                name=user.first_name or user.username,
                surname=user.last_name or ''
            )
            owner_serializer = KittenOwnerSerializer(owner)
            owner_data = owner_serializer.data
        except KittenOwner.DoesNotExist:
            owner_data = None
        
        return Response({
            'user': {
                'id': user.id,
                'username': user.username,
                'email': user.email,
                'first_name': user.first_name,
                'last_name': user.last_name
            },
            'owner': owner_data
        }, status=status.HTTP_200_OK)
        
    except Exception as e:
        return Response({
            'error': f'Ошибка при получении профиля: {str(e)}'
        }, status=status.HTTP_500_INTERNAL_SERVER_ERROR) 