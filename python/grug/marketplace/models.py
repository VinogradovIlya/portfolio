from django.db import models
from django.core.validators import MinValueValidator, MaxValueValidator
from django.utils.text import slugify
from accounts.models import User
# from clinics.models import Clinic
from core.models import TimeStampedModel


class ProductCategory(TimeStampedModel):
    """Категории товаров"""
    name = models.CharField(max_length=100, unique=True, verbose_name='Название')
    slug = models.SlugField(max_length=100, unique=True, verbose_name='URL slug')
    parent = models.ForeignKey('self', on_delete=models.CASCADE, null=True, blank=True, related_name='children')
    description = models.TextField(blank=True, verbose_name='Описание')
    icon = models.CharField(max_length=50, blank=True, verbose_name='Иконка')
    is_active = models.BooleanField(default=True, verbose_name='Активна')
    sort_order = models.PositiveIntegerField(default=0, verbose_name='Порядок сортировки')

    class Meta:
        verbose_name = 'Категория товаров'
        verbose_name_plural = 'Категории товаров'
        ordering = ['sort_order', 'name']

    def save(self, *args, **kwargs):
        if not self.slug:
            self.slug = slugify(self.name)
        super().save(*args, **kwargs)

    def __str__(self):
        if self.parent:
            return f"{self.parent.name} > {self.name}"
        return self.name


class Product(TimeStampedModel):
    """Товары для животных"""
    STATUS_CHOICES = [
        ('draft', 'Черновик'),
        ('active', 'Активен'),
        ('inactive', 'Неактивен'),
        ('out_of_stock', 'Нет в наличии'),
    ]

    # Основная информация
    seller = models.ForeignKey(User, on_delete=models.CASCADE, related_name='products', verbose_name='Продавец')
    name = models.CharField(max_length=200, verbose_name='Название товара')
    slug = models.SlugField(max_length=200, unique=True, verbose_name='URL slug')
    description = models.TextField(verbose_name='Описание')
    short_description = models.CharField(max_length=500, blank=True, verbose_name='Краткое описание')
    
    # Категоризация
    category = models.ForeignKey(ProductCategory, on_delete=models.CASCADE, related_name='products', verbose_name='Категория')
    tags = models.ManyToManyField('ProductTag', blank=True, verbose_name='Теги')
    
    # Цены и наличие
    price = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='Цена')
    old_price = models.DecimalField(max_digits=10, decimal_places=2, null=True, blank=True, verbose_name='Старая цена')
    cost_price = models.DecimalField(max_digits=10, decimal_places=2, null=True, blank=True, verbose_name='Себестоимость')
    
    # Остатки
    stock_quantity = models.PositiveIntegerField(default=0, verbose_name='Количество в наличии')
    reserved_quantity = models.PositiveIntegerField(default=0, verbose_name='Зарезервировано')
    min_stock_level = models.PositiveIntegerField(default=5, verbose_name='Минимальный остаток')
    
    # Характеристики товара
    weight = models.DecimalField(max_digits=8, decimal_places=3, null=True, blank=True, verbose_name='Вес (кг)')
    dimensions = models.CharField(max_length=100, blank=True, verbose_name='Размеры (ДxШxВ)')
    brand = models.ForeignKey('Brand', on_delete=models.SET_NULL, null=True, blank=True, verbose_name='Бренд')
    model = models.CharField(max_length=100, blank=True, verbose_name='Модель')
    
    # Статус и рейтинг
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='draft', verbose_name='Статус')
    is_featured = models.BooleanField(default=False, verbose_name='Рекомендуемый')
    rating = models.DecimalField(max_digits=3, decimal_places=2, default=0, verbose_name='Рейтинг')
    reviews_count = models.PositiveIntegerField(default=0, verbose_name='Количество отзывов')
    
    # SEO и метаданные
    meta_title = models.CharField(max_length=200, blank=True, verbose_name='Meta title')
    meta_description = models.TextField(blank=True, verbose_name='Meta description')
    
    # Статистика
    views_count = models.PositiveIntegerField(default=0, verbose_name='Количество просмотров')
    sales_count = models.PositiveIntegerField(default=0, verbose_name='Количество продаж')

    class Meta:
        verbose_name = 'Товар'
        verbose_name_plural = 'Товары'
        ordering = ['-created_at']
        indexes = [
            models.Index(fields=['status', 'category']),
            models.Index(fields=['price']),
            models.Index(fields=['-created_at']),
        ]

    def save(self, *args, **kwargs):
        if not self.slug:
            self.slug = slugify(self.name)
        super().save(*args, **kwargs)

    @property
    def available_quantity(self):
        return self.stock_quantity - self.reserved_quantity

    @property
    def is_in_stock(self):
        return self.available_quantity > 0

    @property
    def discount_percentage(self):
        if self.old_price and self.old_price > self.price:
            return round(((self.old_price - self.price) / self.old_price) * 100, 1)
        return 0

    def __str__(self):
        return self.name


class ProductTag(TimeStampedModel):
    """Теги товаров"""
    name = models.CharField(max_length=50, unique=True, verbose_name='Название')
    slug = models.SlugField(max_length=50, unique=True, verbose_name='URL slug')

    class Meta:
        verbose_name = 'Тег товара'
        verbose_name_plural = 'Теги товаров'

    def save(self, *args, **kwargs):
        if not self.slug:
            self.slug = slugify(self.name)
        super().save(*args, **kwargs)

    def __str__(self):
        return self.name


class Brand(TimeStampedModel):
    """Бренды товаров"""
    name = models.CharField(max_length=100, unique=True, verbose_name='Название')
    slug = models.SlugField(max_length=100, unique=True, verbose_name='URL slug')
    description = models.TextField(blank=True, verbose_name='Описание')
    website = models.URLField(blank=True, verbose_name='Веб-сайт')
    is_active = models.BooleanField(default=True, verbose_name='Активен')

    class Meta:
        verbose_name = 'Бренд'
        verbose_name_plural = 'Бренды'
        ordering = ['name']

    def save(self, *args, **kwargs):
        if not self.slug:
            self.slug = slugify(self.name)
        super().save(*args, **kwargs)

    def __str__(self):
        return self.name


class Cart(TimeStampedModel):
    """Корзина покупателя"""
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='cart', verbose_name='Пользователь')

    class Meta:
        verbose_name = 'Корзина'
        verbose_name_plural = 'Корзины'

    @property
    def total_amount(self):
        return sum(item.total_price for item in self.items.all())

    @property
    def total_items(self):
        return sum(item.quantity for item in self.items.all())

    def __str__(self):
        return f"Корзина {self.user.email}"


class CartItem(TimeStampedModel):
    """Товар в корзине"""
    cart = models.ForeignKey(Cart, on_delete=models.CASCADE, related_name='items', verbose_name='Корзина')
    product = models.ForeignKey(Product, on_delete=models.CASCADE, verbose_name='Товар')
    quantity = models.PositiveIntegerField(default=1, verbose_name='Количество')
    price = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='Цена за единицу')

    class Meta:
        verbose_name = 'Товар в корзине'
        verbose_name_plural = 'Товары в корзине'
        unique_together = ('cart', 'product')

    @property
    def total_price(self):
        return self.price * self.quantity

    def save(self, *args, **kwargs):
        if not self.price:
            self.price = self.product.price
        super().save(*args, **kwargs)

    def __str__(self):
        return f"{self.product.name} x {self.quantity}"


class Order(TimeStampedModel):
    """Заказы"""
    STATUS_CHOICES = [
        ('pending', 'В ожидании'),
        ('confirmed', 'Подтвержден'),
        ('processing', 'В обработке'),
        ('shipped', 'Отправлен'),
        ('delivered', 'Доставлен'),
        ('cancelled', 'Отменен'),
        ('returned', 'Возвращен'),
    ]

    PAYMENT_STATUS_CHOICES = [
        ('pending', 'Ожидает оплаты'),
        ('paid', 'Оплачен'),
        ('failed', 'Ошибка оплаты'),
        ('refunded', 'Возвращен'),
    ]

    # Основная информация
    order_number = models.CharField(max_length=20, unique=True, verbose_name='Номер заказа')
    buyer = models.ForeignKey(User, on_delete=models.CASCADE, related_name='orders', verbose_name='Покупатель')
    
    # Статусы
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='pending', verbose_name='Статус')
    payment_status = models.CharField(max_length=20, choices=PAYMENT_STATUS_CHOICES, default='pending', verbose_name='Статус оплаты')
    
    # Суммы
    subtotal = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='Сумма товаров')
    delivery_cost = models.DecimalField(max_digits=8, decimal_places=2, default=0, verbose_name='Стоимость доставки')
    total_amount = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='Общая сумма')
    
    # Доставка
    delivery_address = models.TextField(verbose_name='Адрес доставки')
    delivery_city = models.CharField(max_length=100, verbose_name='Город доставки')
    delivery_phone = models.CharField(max_length=20, verbose_name='Телефон получателя')
    delivery_notes = models.TextField(blank=True, verbose_name='Комментарии к доставке')
    
    # Даты
    estimated_delivery_date = models.DateTimeField(null=True, blank=True, verbose_name='Ожидаемая дата доставки')
    delivered_at = models.DateTimeField(null=True, blank=True, verbose_name='Дата доставки')
    
    # Дополнительная информация
    notes = models.TextField(blank=True, verbose_name='Комментарии к заказу')

    class Meta:
        verbose_name = 'Заказ'
        verbose_name_plural = 'Заказы'
        ordering = ['-created_at']

    def save(self, *args, **kwargs):
        if not self.order_number:
            # Генерируем уникальный номер заказа
            import uuid
            self.order_number = f"ORD-{uuid.uuid4().hex[:8].upper()}"
        super().save(*args, **kwargs)

    def __str__(self):
        return f"Заказ {self.order_number}"


class OrderItem(TimeStampedModel):
    """Товар в заказе"""
    order = models.ForeignKey(Order, on_delete=models.CASCADE, related_name='items', verbose_name='Заказ')
    product = models.ForeignKey(Product, on_delete=models.CASCADE, verbose_name='Товар')
    quantity = models.PositiveIntegerField(verbose_name='Количество')
    price = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='Цена за единицу')
    total_price = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='Общая стоимость')

    class Meta:
        verbose_name = 'Товар в заказе'
        verbose_name_plural = 'Товары в заказе'

    def save(self, *args, **kwargs):
        self.total_price = self.price * self.quantity
        super().save(*args, **kwargs)

    def __str__(self):
        return f"{self.product.name} x {self.quantity}"


class ProductReview(TimeStampedModel):
    """Отзывы на товары"""
    product = models.ForeignKey(Product, on_delete=models.CASCADE, related_name='product_reviews', verbose_name='Товар')
    author = models.ForeignKey(User, on_delete=models.CASCADE, related_name='product_reviews', verbose_name='Автор')
    order_item = models.OneToOneField(OrderItem, on_delete=models.CASCADE, null=True, blank=True, verbose_name='Товар из заказа')
    
    rating = models.PositiveIntegerField(
        validators=[MinValueValidator(1), MaxValueValidator(5)],
        verbose_name='Оценка'
    )
    title = models.CharField(max_length=200, verbose_name='Заголовок')
    content = models.TextField(verbose_name='Текст отзыва')
    
    # Плюсы и минусы
    pros = models.TextField(blank=True, verbose_name='Достоинства')
    cons = models.TextField(blank=True, verbose_name='Недостатки')
    
    # Модерация
    is_approved = models.BooleanField(default=False, verbose_name='Одобрен')
    is_verified_purchase = models.BooleanField(default=False, verbose_name='Проверенная покупка')

    class Meta:
        verbose_name = 'Отзыв на товар'
        verbose_name_plural = 'Отзывы на товары'
        ordering = ['-created_at']
        unique_together = ('product', 'author')

    def __str__(self):
        return f"Отзыв на {self.product.name} - {self.rating}/5"