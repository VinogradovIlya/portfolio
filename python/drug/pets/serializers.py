from rest_framework import serializers
from .models import Pet, Breed, PetPhoto

class BreedSerializer(serializers.ModelSerializer):
    class Meta:
        model = Breed
        fields = ('id', 'name', 'species', 'description')

class PetPhotoSerializer(serializers.ModelSerializer):
    class Meta:
        model = PetPhoto
        fields = ('id', 'photo', 'description', 'created_at')

class PetSerializer(serializers.ModelSerializer):
    breed = BreedSerializer(read_only=True)
    breed_id = serializers.IntegerField(write_only=True)
    photos = PetPhotoSerializer(many=True, read_only=True)
    age_in_years = serializers.ReadOnlyField()

    class Meta:
        model = Pet
        fields = (
            'id', 'name', 'breed', 'breed_id', 'birthday', 'gender', 
            'color', 'weight', 'passport_number', 'is_chipped', 
            'chip_number', 'description', 'special_needs', 
            'main_photo', 'photos', 'age_in_years', 'created_at'
        )

class PetCreateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Pet
        fields = (
            'name', 'breed', 'birthday', 'gender', 'color', 
            'weight', 'passport_number', 'is_chipped', 
            'chip_number', 'description', 'special_needs', 'main_photo'
        )

    def create(self, validated_data):
        validated_data['owner'] = self.context['request'].user
        return super().create(validated_data)