from rest_framework import viewsets, status, permissions
from rest_framework.decorators import action
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated, AllowAny
from django.db.models import Avg, Count
from django.shortcuts import get_object_or_404
from .models import KittenOwner, Cat, Rating, Images
from .serializers import (
    KittenOwnerSerializer, CatSerializer, RatingSerializer, 
    RatingCreateSerializer, ImagesSerializer
)

class KittenOwnerViewSet(viewsets.ModelViewSet):
    """
    API endpoint для управления владельцами кошек
    """
    queryset = KittenOwner.objects.all()
    serializer_class = KittenOwnerSerializer
    permission_classes = [IsAuthenticated]

    @action(detail=True, methods=['get'])
    def cats(self, request, pk=None):
        """Получить всех кошек конкретного владельца"""
        owner = self.get_object()
        cats = Cat.objects.filter(kitten_owner=owner)
        serializer = CatSerializer(cats, many=True)
        return Response(serializer.data)

class CatViewSet(viewsets.ModelViewSet):
    """
    API endpoint для управления кошками
    """
    queryset = Cat.objects.select_related('kitten_owner').all()
    serializer_class = CatSerializer
    permission_classes = [IsAuthenticated]

    def get_queryset(self):
        queryset = Cat.objects.select_related('kitten_owner').all()
        
        # Фильтрация по породе
        breed = self.request.query_params.get('breed', None)
        if breed:
            queryset = queryset.filter(kitten_breed__icontains=breed)
        
        # Фильтрация по возрасту
        min_age = self.request.query_params.get('min_age', None)
        if min_age:
            queryset = queryset.filter(mounts__gte=min_age)
        
        max_age = self.request.query_params.get('max_age', None)
        if max_age:
            queryset = queryset.filter(mounts__lte=max_age)
        
        # Сортировка
        sort_by = self.request.query_params.get('sort_by', None)
        if sort_by == 'rating':
            queryset = queryset.annotate(
                avg_rating=Avg('rating__rating'),
                ratings_count=Count('rating')
            ).order_by('-avg_rating')
        elif sort_by == 'age':
            queryset = queryset.order_by('mounts')
        elif sort_by == 'breed':
            queryset = queryset.order_by('kitten_breed')
        
        return queryset

    def perform_create(self, serializer):
        serializer.save()

    @action(detail=True, methods=['get'])
    def ratings(self, request, pk=None):
        """Получить все оценки конкретной кошки"""
        cat = self.get_object()
        ratings = Rating.objects.filter(cat=cat).select_related('author')
        serializer = RatingSerializer(ratings, many=True)
        return Response(serializer.data)

    @action(detail=False, methods=['get'])
    def breeds(self, request):
        """Получить список всех пород"""
        breeds = Cat.objects.values_list('kitten_breed', flat=True).distinct()
        return Response(list(breeds))

    @action(detail=False, methods=['get'])
    def top_rated(self, request):
        """Получить топ-10 кошек по рейтингу"""
        top_cats = Cat.objects.annotate(
            avg_rating=Avg('rating__rating'),
            ratings_count=Count('rating')
        ).filter(ratings_count__gt=0).order_by('-avg_rating')[:10]
        
        serializer = CatSerializer(top_cats, many=True)
        return Response(serializer.data)

class RatingViewSet(viewsets.ModelViewSet):
    """
    API endpoint для управления рейтингами
    """
    queryset = Rating.objects.select_related('cat', 'author').all()
    serializer_class = RatingSerializer
    permission_classes = [IsAuthenticated]

    def get_serializer_class(self):
        if self.action == 'create':
            return RatingCreateSerializer
        return RatingSerializer

    def perform_create(self, serializer):
        # Проверяем, не существует ли уже оценка от этого автора для этой кошки
        existing_rating = Rating.objects.filter(
            cat=serializer.validated_data['cat'],
            author=serializer.validated_data['author']
        ).first()
        
        if existing_rating:
            # Обновляем существующую оценку
            existing_rating.rating = serializer.validated_data['rating']
            existing_rating.save()
            return existing_rating
        else:
            # Создаем новую оценку
            return serializer.save()

    @action(detail=False, methods=['get'])
    def my_ratings(self, request):
        """Получить все оценки текущего пользователя"""
        # В реальном приложении здесь была бы проверка JWT токена
        # Пока возвращаем все оценки
        ratings = Rating.objects.select_related('cat', 'author').all()
        serializer = RatingSerializer(ratings, many=True)
        return Response(serializer.data)

class ImagesViewSet(viewsets.ModelViewSet):
    """
    API endpoint для управления изображениями
    """
    queryset = Images.objects.select_related('cat_photo', 'author').all()
    serializer_class = ImagesSerializer
    permission_classes = [IsAuthenticated]

    def perform_create(self, serializer):
        serializer.save() 