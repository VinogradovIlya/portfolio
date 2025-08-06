from rest_framework import serializers
from .models import KittenOwner, Cat, Rating, Images

class KittenOwnerSerializer(serializers.ModelSerializer):
    class Meta:
        model = KittenOwner
        fields = ['id', 'name', 'surname', 'patronymic']

class CatSerializer(serializers.ModelSerializer):
    kitten_owner = KittenOwnerSerializer(read_only=True)
    average_rating = serializers.FloatField(read_only=True)
    ratings_count = serializers.IntegerField(read_only=True)
    
    class Meta:
        model = Cat
        fields = ['id', 'colors', 'mounts', 'kitten_breed', 'description', 'photo', 'kitten_owner', 'average_rating', 'ratings_count']

class RatingSerializer(serializers.ModelSerializer):
    cat = CatSerializer(read_only=True)
    author = KittenOwnerSerializer(read_only=True)
    
    class Meta:
        model = Rating
        fields = ['id', 'cat', 'author', 'rating']

class RatingCreateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Rating
        fields = ['cat', 'author', 'rating']

class ImagesSerializer(serializers.ModelSerializer):
    cat_photo = CatSerializer(read_only=True)
    author = KittenOwnerSerializer(read_only=True)
    
    class Meta:
        model = Images
        fields = ['id', 'cat_photo', 'author'] 