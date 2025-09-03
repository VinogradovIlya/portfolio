import factory
from factory import Faker, SubFactory
from factory.django import DjangoModelFactory
from django.contrib.auth import get_user_model
from accounts.models import UserProfile

User = get_user_model()


class UserFactory(DjangoModelFactory):
    """Фабрика для создания пользователей"""
    
    class Meta:
        model = User
    
    email = Faker('email')
    user_type = 'pet_owner'
    phone = Faker('phone_number', locale='ru_RU')
    city = Faker('city', locale='ru_RU')
    
    is_verified = False
    is_active = True
    subscriber = False
    
    @factory.post_generation
    def password(self, create, extracted, **kwargs):
        if not create:
            return
        
        password = extracted or 'testpassword123'
        self.set_password(password)
        self.save()


class VerifiedUserFactory(UserFactory):
    """Фабрика для верифицированных пользователей"""
    is_verified = True


class VeterinarianUserFactory(UserFactory):
    """Фабрика для ветеринаров"""
    user_type = 'veterinarian'
    is_verified = True


class ClinicAdminUserFactory(UserFactory):
    """Фабрика для администраторов клиник"""
    user_type = 'clinic_admin'
    is_verified = True


class BusinessUserFactory(UserFactory):
    """Фабрика для бизнес-пользователей"""
    user_type = 'business'
    is_verified = True


class AdminUserFactory(UserFactory):
    """Фабрика для администраторов"""
    user_type = 'admin'
    is_verified = True
    is_staff = True
    is_superuser = True


class UserProfileFactory(DjangoModelFactory):
    """Фабрика для профилей пользователей"""
    
    class Meta:
        model = UserProfile
    
    user = SubFactory(UserFactory)
    first_name = Faker('first_name', locale='ru_RU')
    last_name = Faker('last_name', locale='ru_RU')
    middle_name = Faker('middle_name', locale='ru_RU')
    birthday = Faker('date_of_birth', minimum_age=18, maximum_age=80)
    gender = factory.Iterator(['m', 'f', 'unknown'])
    bio = Faker('text', max_nb_chars=200)


class UserWithProfileFactory(UserFactory):
    """Фабрика пользователя с профилем"""
    
    profile = factory.RelatedFactory(
        UserProfileFactory,
        'user',
        first_name=Faker('first_name', locale='ru_RU'),
        last_name=Faker('last_name', locale='ru_RU')
    )


class InactiveUserFactory(UserFactory):
    """Заблокированный пользователь"""
    is_active = False


class UnverifiedUserFactory(UserFactory):
    """Неверифицированный пользователь"""
    is_verified = False


class SubscriberUserFactory(UserFactory):
    """Подписчик рассылки"""
    subscriber = True
    is_verified = True