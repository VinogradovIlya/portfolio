from django.urls import path, include
from . import views


app_name = 'core'

urlpatterns = [
    path('', views.home, name='home'),
    path('projects/', views.projects, name='projects'),
]
