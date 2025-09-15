from rest_framework import serializers
from .models import Breed, Pet, PetPhoto


class PetProfileSerializer(serializers.ModelSerializer):
    # owner = ?
    class Meta:
        model = Pet
        fields = ('name', 'breed', 'birthday', 'gender', 'color',
                  'weight', 'passport_number', 'is_chipped', 'chip_number', 'description', 'special_needs',
                  'main_photo')
