from django.db import models

# Create your models here.


class Skill(models.Model):
    name = models.CharField(max_length=30)
    description = models.TextField()
    years_experience = models.PositiveIntegerField()

    def __str__(self):
        return f'{self.name} ({self.years_experience} лет)'

    class Meta:
        ordering = ['name']


class Project(models.Model):
    CATEGORY_CHOICES = [
        ('c_cpp', 'C/C++'),
        ('python', 'Python'),
        ('database', 'Database'),
        ('devops', 'DevOps'),
        ('telegram', 'telegram'),
    ]
    title = models.CharField(max_length=100)
    description = models.TextField()
    category = models.CharField(max_length=20, choices=CATEGORY_CHOICES)
    github_url = models.URLField()
    is_featured = models.BooleanField(default=False)
    created_at = models.DateField(auto_now_add=True)

    def __str__(self):
        return f'Project -- {self.title}: \n{self.description} \n{self.category} \n {self.github_url}'

    class Meta:
        ordering = ['created_at']

class Technologies(models.Model):
    CATEGORY_CHOICES = [
        ('c_cpp', 'C/C++'),
        ('gcovr', 'GCOVR'),
        ('valgrind', 'Valgrind'),
        ('gnu make', 'GNU Make'),
        ('check', 'Check'),
        ('ncurses', 'Ncurses'),
        ('python', 'Python'),
        ('flask', 'Flask'),
        ('fastapi', 'FastAPI'),
        ('django', 'Django'),
        ('database', 'Database'),
        ('mysql', 'MySQL'),
        ('sqlalchemy', 'SQLAlchemy'),
        ('postgersql', 'PostgreSQL'),
        ('django orm', 'Django ORM'),
        ('devops', 'DevOps'),
        ('linux', 'Linux'),
    ]
    name = models.CharField(max_length=30, choices=CATEGORY_CHOICES)
    projects = models.ManyToManyField(Project)

    def __str__(self):
        return f'name: {self.name}'