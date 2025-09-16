from rest_framework import status, permissions
from rest_framework.decorators import api_view, permission_classes
from rest_framework.response import Response
from .models import Pet, Breed
from .serializers import PetSerializer, PetCreateSerializer, BreedSerializer

@api_view(['GET', 'POST'])
@permission_classes([permissions.IsAuthenticated])
def pets_list(request):
    """
    GET: Получить всех питомцев текущего пользователя
    POST: Создать нового питомца
    """
    if request.method == 'GET':
        pets = Pet.objects.filter(owner=request.user)
        serializer = PetSerializer(pets, many=True)
        return Response(serializer.data)
    
    elif request.method == 'POST':
        serializer = PetCreateSerializer(data=request.data, context={'request': request})
        if serializer.is_valid():
            pet = serializer.save()
            return Response(
                PetSerializer(pet).data, 
                status=status.HTTP_201_CREATED
            )
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET', 'PUT', 'DELETE'])
@permission_classes([permissions.IsAuthenticated])
def pet_detail(request, pet_id):
    """
    GET: Получить конкретного питомца
    PUT: Обновить питомца
    DELETE: Удалить питомца
    """
    try:
        pet = Pet.objects.get(id=pet_id, owner=request.user)
    except Pet.DoesNotExist:
        return Response(
            {'error': 'Питомец не найден'}, 
            status=status.HTTP_404_NOT_FOUND
        )
    
    if request.method == 'GET':
        serializer = PetSerializer(pet)
        return Response(serializer.data)
    
    elif request.method == 'PUT':
        serializer = PetCreateSerializer(pet, data=request.data, partial=True)
        if serializer.is_valid():
            pet = serializer.save()
            return Response(PetSerializer(pet).data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    
    elif request.method == 'DELETE':
        pet.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)

@api_view(['GET'])
@permission_classes([permissions.AllowAny])
def breeds_list(request):
    """Получить список всех пород"""
    breeds = Breed.objects.all()
    serializer = BreedSerializer(breeds, many=True)
    return Response(serializer.data)