from django.contrib import admin
from .models import Project, Skill

# Register your models here.


@admin.register(Project)
class ProjectAdmin(admin.ModelAdmin):
    list_display = ('title', 'category', 'is_featured', 'created_at')
    list_filter = ('category', 'is_featured', 'created_at')
    search_fields = ('title', 'description')
    list_editable = ('is_featured',)
    ordering = ('-created_at',)

    fieldsets = (
        (None, {
            'fields': ('title', 'description', 'category')
        }),
        ('Ссылки', {
            'fields': ('github_url',),
        }),
        ('Настройки', {
            'fields': ('is_featured',),
        }),
    )


@admin.register(Skill)
class SkillAdmin(admin.ModelAdmin):
    list_display = ('name', 'years_experience')
    search_fields = ('name',)
    ordering = ('name',)

    fields = ('name', 'description', 'years_experience')
