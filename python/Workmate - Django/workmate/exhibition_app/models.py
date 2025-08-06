from django.db import models

# Create your models here.


class KittenOwner(models.Model):
    name = models.CharField(max_length=50)
    surname = models.CharField(max_length=50)
    patronymic = models.CharField(max_length=50)

    def __str__(self):
        return f'name: {self.name} surname: {self.surname}, patronymic: {self.patronymic}'


class Cat(models.Model):
    colors = models.CharField(max_length=50)
    mounts = models.IntegerField()
    kitten_breed = models.CharField(max_length=50)
    description = models.TextField()
    photo = models.ImageField(upload_to='cats/')
    kitten_owner = models.ForeignKey(KittenOwner, on_delete=models.CASCADE)

    def __str__(self):
        return f'color: {self.colors}, mounts: {self.mounts}, kitten breed: {self.kitten_breed}, desc: {self.description}, kitten owner: {self.kitten_owner}'


class Images(models.Model):
    cat_photo = models.ForeignKey(Cat, on_delete=models.CASCADE)
    author = models.ForeignKey(KittenOwner, on_delete=models.CASCADE)

    def __str__(self):
        return  f'Photo of {self.cat_photo} by {self.author}'


class Rating(models.Model):
    RATING_CHOICES = [
        (1, '1'), (2, '2'), (3, '3'), (4, '4'), (5, '5')
    ]
    
    cat = models.ForeignKey(Cat, on_delete=models.CASCADE)
    author = models.ForeignKey(KittenOwner, on_delete=models.CASCADE)
    rating = models.IntegerField(choices=RATING_CHOICES)
    
    class Meta:
        unique_together = ('cat', 'author') 
    
    def __str__(self):
        return f'Rating {self.rating} for {self.cat} by {self.author}'