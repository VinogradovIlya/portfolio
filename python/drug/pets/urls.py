from django.urls import path
from . import views

app_name = 'pets'

urlpatterns = [
    path('', views.pets_list, name='pets_list'),              # GET/POST /api/pet/
    path('<int:pet_id>/', views.pet_detail, name='pet_detail'), # GET/PUT/DELETE /api/pet/1/
    path('breeds/', views.breeds_list, name='breeds_list'),   # GET /api/pet/breeds/
]