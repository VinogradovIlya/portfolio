from rest_framework import serializers
from django.contrib.auth import authenticate
from django.contrib.auth.password_validation import validate_password
from .models import User, UserProfile


class UserRegistrationSerializer(serializers.ModelSerializer):
    password = serializers.CharField(
        write_only=True, min_length=8, max_length=16)
    password_confirm = serializers.CharField(write_only=True)

    class Meta:
        model = User
        fields = ('email', 'phone', 'password', 'password_confirm', 'city')
        extra_kwargs = {
            'email': {'required': True},
            'phone': {'required': True},
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


class UserSerializer(serializers.ModelSerializer):
    profile = UserProfileSerializer(read_only=True)

    class Meta:
        model = User
        fields = ('id', 'email', 'user_type', 'phone',
                  'is_verified', 'profile', 'date_joined')
        read_only_fields = ('id', 'is_verified', 'date_joined')
