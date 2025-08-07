from django.shortcuts import render
from .models import Project, Skill

# Create your views here.

def home(request):
    return render(request, 'core/index.html')

def projects(request):
    projects = Project.objects.all()
    skills = Skill.objects.all()
    return render(request, 'core/projects.html')