from django.urls import path
from . import views

app_name = 'exhibition_app'

urlpatterns = [
    path('', views.home, name='home'),
    path('add-owner/', views.add_owner, name='add_owner'),
    path('add-cat/', views.add_cat, name='add_cat'),
    path('edit-cat/<int:pk>/', views.edit_cat, name='edit_cat'),
    path('delete-cat/<int:pk>/', views.delete_cat, name='delete_cat'),
    path('list-cats/', views.list_cats, name='list_cats'),
    path('add-rating/', views.add_rating, name='add_rating'),
    path('ratings/', views.ratings, name='ratings'),
    path('cats/', views.all_cats, name='all_cats'),
    path('cats/<str:breed>/', views.all_cats, name='cats_by_breeds'),
    path('cat/<int:pk>/', views.get_cat_info, name='cat_info'),
    path('breeds/', views.kitten_breeds, name='kitten_breeds'),
]