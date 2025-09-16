from rest_framework import serializers
from django.contrib.auth import authenticate
from django.contrib.auth.password_validation import validate_password
from .models import User, UserProfile


class UserRegistrationSerializer(serializers.ModelSerializer):
    """Сериализатор для регистрации пользователя"""
    password = serializers.CharField(
        write_only=True,
        min_length=8,
        max_length=16,
        help_text="Пароль от 8 до 16 символов"
    )
    password_confirm = serializers.CharField(
        write_only=True,
        help_text="Подтверждение пароля"
    )

    class Meta:
        model = User
        fields = ('email', 'phone', 'password', 'password_confirm', 'city')
        extra_kwargs = {
            'email': {
                'required': True,
                'help_text': 'Действующий email адрес'
            },
            'phone': {
                'required': True,
                'help_text': 'Номер телефона в формате +7XXXXXXXXXX'
            },
            'city': {
                'help_text': 'Город проживания'
            }
        }

    def validate(self, attrs):
        if attrs['password'] != attrs['password_confirm']:
            raise serializers.ValidationError({
                'password_confirm': 'Пароли не совпадают'
            })
        return attrs

    def validate_password(self, value):
        validate_password(value)
        return value

    def create(self, validated_data):
        validated_data.pop('password_confirm', None)
        user = User.objects.create_user(**validated_data)
        return user


class UserLoginSerializer(serializers.Serializer):
    email = serializers.EmailField()
    password = serializers.CharField(write_only=True)

    def validate(self, attrs):
        email = attrs.get('email')
        password = attrs.get('password')

        if email and password:
            user = authenticate(email=email, password=password)

            if not user:
                raise serializers.ValidationError('Неверный email или пароль')

            if not user.is_active:
                raise serializers.ValidationError('Аккаунт заблокирован')

            attrs['user'] = user
            return attrs
        else:
            raise serializers.ValidationError(
                'Необходимо указать email и пароль')


class UserProfileSerializer(serializers.ModelSerializer):
    full_name = serializers.ReadOnlyField()

    class Meta:
        model = UserProfile
        fields = ('first_name', 'last_name', 'middle_name',
                  'birthday', 'gender', 'avatar', 'bio', 'full_name')


# accounts/serializers.py
class UserSerializer(serializers.ModelSerializer):
    profile = UserProfileSerializer(read_only=True)
    
    first_name = serializers.CharField(write_only=True, required=False)
    last_name = serializers.CharField(write_only=True, required=False)
    bio = serializers.CharField(write_only=True, required=False)

    class Meta:
        model = User
        fields = ('id', 'email', 'user_type', 'phone', 'city',
                  'is_verified', 'profile', 'date_joined',
                  'first_name', 'last_name', 'bio')  # поля для записи
        read_only_fields = ('id', 'is_verified', 'date_joined')

    def update(self, instance, validated_data):
        # Извлекаем данные профиля
        profile_data = {}
        for field in ['first_name', 'last_name', 'bio']:
            if field in validated_data:
                profile_data[field] = validated_data.pop(field)
        
        # Обновляем User
        for attr, value in validated_data.items():
            setattr(instance, attr, value)
        instance.save()
        
        # Обновляем или создаем Profile
        if profile_data:
            profile, created = UserProfile.objects.get_or_create(user=instance)
            for attr, value in profile_data.items():
                setattr(profile, attr, value)
            profile.save()
        
        return instance


class PasswordRecoverySerializer(serializers.Serializer):
    email = serializers.EmailField()

    def validate_email(self, value):
        try:
            user = User.objects.get(email=value)
        except User.DoesNotExist:
            raise serializers.ValidationError("Пользователь с таким email не найден")
        return value

    def save(self):
        email = self.validated_data['email']
        user = User.objects.get(email=email)
        
        # Здесь логика отправки email
        # Пока просто возвращаем пользователя
        return user