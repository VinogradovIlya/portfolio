from django.db import models
from pets.models import Pet
from clinics.models import Veterinarian, Clinic, Service
from core.models import TimeStampedModel


class MedicalRecord(TimeStampedModel):
    """Медицинская карта питомца"""
    pet = models.OneToOneField(
        Pet, on_delete=models.CASCADE, related_name='medical_record')
    notes = models.TextField(blank=True, verbose_name='Общие заметки')

    class Meta:
        verbose_name = 'Медицинская карта'
        verbose_name_plural = 'Медицинские карты'

    def __str__(self):
        return f"Карта {self.pet.name}"


class Appointment(TimeStampedModel):
    """Запись на прием"""
    STATUS_CHOICES = [
        ('scheduled', 'Запланирована'),
        ('confirmed', 'Подтверждена'),
        ('in_progress', 'Идет прием'),
        ('completed', 'Завершена'),
        ('cancelled', 'Отменена'),
        ('no_show', 'Не явился'),
    ]

    pet = models.ForeignKey(Pet, on_delete=models.CASCADE,
                            related_name='appointments')
    veterinarian = models.ForeignKey(
        Veterinarian, on_delete=models.CASCADE, related_name='appointments')
    clinic = models.ForeignKey(
        Clinic, on_delete=models.CASCADE, related_name='appointments')
    service = models.ForeignKey(
        Service, on_delete=models.CASCADE, related_name='appointments')

    # Время и дата
    scheduled_date = models.DateTimeField(verbose_name='Дата и время приема')
    duration_minutes = models.PositiveIntegerField(
        verbose_name='Длительность (мин)')

    # Статус и цена
    status = models.CharField(
        max_length=20, choices=STATUS_CHOICES, default='scheduled')
    price = models.DecimalField(
        max_digits=8, decimal_places=2, verbose_name='Стоимость')

    # Заметки
    owner_notes = models.TextField(
        blank=True, verbose_name='Заметки владельца')
    vet_notes = models.TextField(blank=True, verbose_name='Заметки ветеринара')

    class Meta:
        verbose_name = 'Запись на прием'
        verbose_name_plural = 'Записи на прием'
        ordering = ['-scheduled_date']

    def __str__(self):
        return f"{self.pet.name} - {self.veterinarian} ({self.scheduled_date})"


class MedicalVisit(TimeStampedModel):
    """Посещение ветеринара"""
    medical_record = models.ForeignKey(
        MedicalRecord, on_delete=models.CASCADE, related_name='visits')
    appointment = models.OneToOneField(
        Appointment, on_delete=models.CASCADE, null=True, blank=True)

    veterinarian = models.ForeignKey(Veterinarian, on_delete=models.CASCADE)
    clinic = models.ForeignKey(Clinic, on_delete=models.CASCADE)
    visit_date = models.DateTimeField(verbose_name='Дата визита')

    # Осмотр
    complaint = models.TextField(verbose_name='Жалобы')
    examination = models.TextField(verbose_name='Результаты осмотра')
    diagnosis = models.TextField(verbose_name='Диагноз')
    treatment_plan = models.TextField(verbose_name='План лечения')
    recommendations = models.TextField(blank=True, verbose_name='Рекомендации')

    # Следующий визит
    next_visit_date = models.DateTimeField(
        null=True, blank=True, verbose_name='Дата следующего визита')

    # Вес на момент визита
    weight = models.DecimalField(
        max_digits=6, decimal_places=2, null=True, blank=True, verbose_name='Вес (кг)')

    class Meta:
        verbose_name = 'Визит к ветеринару'
        verbose_name_plural = 'Визиты к ветеринару'
        ordering = ['-visit_date']

    def __str__(self):
        return f"{self.medical_record.pet.name} - {self.visit_date.date()}"


class Vaccination(TimeStampedModel):
    """Вакцинация"""
    visit = models.ForeignKey(
        MedicalVisit, on_delete=models.CASCADE, related_name='vaccinations')
    vaccine_type = models.ForeignKey('VaccineType', on_delete=models.CASCADE)
    vaccine_name = models.CharField(
        max_length=100, verbose_name='Название вакцины')
    batch_number = models.CharField(max_length=50, verbose_name='Номер партии')
    vaccination_date = models.DateField(verbose_name='Дата вакцинации')
    next_vaccination_date = models.DateField(
        null=True, blank=True, verbose_name='Дата следующей вакцинации')
    side_effects = models.TextField(
        blank=True, verbose_name='Побочные эффекты')

    class Meta:
        verbose_name = 'Вакцинация'
        verbose_name_plural = 'Вакцинации'

    def __str__(self):
        return f"{self.vaccine_type.name} - {self.vaccination_date}"


class VaccineType(TimeStampedModel):
    """Типы вакцин"""
    name = models.CharField(max_length=100, unique=True,
                            verbose_name='Название')
    description = models.TextField(blank=True, verbose_name='Описание')
    """ TODO 
    ❯ ./manage.py makemigrations
    SystemCheckError: System check identified some issues:

    ERRORS:
    <function ManyToManyField.contribute_to_class.<locals>.resolve_through_model at 0x104a8a520>: (models.E022) <function ManyToManyField.contribute_to_class.<locals>.resolve_through_model at 0x104a8a520> contains a lazy reference to pets.breed_species, but app 'pets' doesn't provide model 'breed_species'.
    medical.VaccineType.species: (fields.E331) Field specifies a many-to-many relation through model 'pets.Breed_species', which has not been installed.
    species = models.ManyToManyField('pets.Breed', through='pets.Breed_species', verbose_name='Виды животных')
    """
    frequency_months = models.PositiveIntegerField(
        verbose_name='Периодичность (месяцы)')

    class Meta:
        verbose_name = 'Тип вакцины'
        verbose_name_plural = 'Типы вакцин'

    def __str__(self):
        return self.name


class Treatment(TimeStampedModel):
    """Лечебная процедура"""
    visit = models.ForeignKey(
        MedicalVisit, on_delete=models.CASCADE, related_name='treatments')
    procedure_type = models.ForeignKey(
        'ProcedureType', on_delete=models.CASCADE)
    description = models.TextField(verbose_name='Описание процедуры')
    medications = models.TextField(
        blank=True, verbose_name='Назначенные препараты')
    cost = models.DecimalField(
        max_digits=8, decimal_places=2, verbose_name='Стоимость')

    class Meta:
        verbose_name = 'Процедура'
        verbose_name_plural = 'Процедуры'

    def __str__(self):
        return f"{self.procedure_type.name} - {self.visit.visit_date.date()}"


class ProcedureType(TimeStampedModel):
    """Типы процедур"""
    name = models.CharField(max_length=100, unique=True,
                            verbose_name='Название')
    description = models.TextField(blank=True, verbose_name='Описание')
    # лечение, профилактика, диагностика
    category = models.CharField(max_length=50, verbose_name='Категория')

    class Meta:
        verbose_name = 'Тип процедуры'
        verbose_name_plural = 'Типы процедур'

    def __str__(self):
        return self.name
