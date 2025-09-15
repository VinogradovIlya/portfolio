from rest_framework import status, permissions
from rest_framework.decorators import api_view, permission_classes
from rest_framework.response import Response
from rest_framework.authtoken.models import Token
from .serializers import PetProfileSerializer


@api_view(['GET'])
@permission_classes([permissions.IsAuthenticated])
def get_pet(request):
    serializer = PetProfileSerializer(request.user)
    return Response(serializer.data)