from django.contrib import admin
from .models import Skill, Project, Technologies

# Register your models here.


@admin.register(Skill)
class SkillAdmin(admin.ModelAdmin):
    list_display = ['name', 'years_experience']
    search_fields = ['name']
    ordering = ['name']


@admin.register(Project)
class ProjectAdmin(admin.ModelAdmin):
    list_display = ['title', 'category', 'is_featured', 'created_at']
    list_filter = ['category', 'technologies', 'is_featured', 'created_at']
    search_fields = ['title', 'technologies', 'description']
    ordering = ['-created_at']

@admin.register(Technologies)
class TechnologiesAdmin(admin.ModelAdmin):
    # list_display = ['name', 'projects']
    list_filter = ['name', 'projects']
    search_fields = ['name', 'procets']