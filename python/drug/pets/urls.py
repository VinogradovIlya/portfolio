from django.urls import path
from . import views

app_name = 'pets'

urlpatterns = [
    path('', views.get_pet, name='owner_pets'),
]