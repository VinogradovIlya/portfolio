# Выставка кошек - Django приложение

## 🐱 Описание проекта

Веб-приложение для управления выставкой кошек с возможностью добавления, редактирования и оценки котят. Включает HTML формы, API с JWT авторизацией и документацию Swagger.

## ✨ Функциональность

### Веб-интерфейс
- ✅ Добавление/редактирование владельцев кошек
- ✅ Добавление/редактирование кошек с фото
- ✅ Система рейтингов (1-5 звезд)
- ✅ Просмотр списка кошек с фильтрацией
- ✅ Адаптивный дизайн

### API (REST)
- ✅ JWT авторизация пользователей
- ✅ CRUD операции для всех моделей
- ✅ Фильтрация и сортировка
- ✅ Swagger документация

## 🚀 Быстрый запуск

### 1. Клонирование и настройка

```bash
# Клонировать репозиторий
git clone <repository-url>
cd workmate

# Создать виртуальное окружение
python -m venv venv

# Активировать виртуальное окружение
# Windows:
venv\Scripts\activate
# macOS/Linux:
source venv/bin/activate
```

### 2. Установка зависимостей

```bash
# Установить все зависимости
pip install -r requirements.txt
```

### 3. Настройка базы данных

```bash
# Применить миграции
python manage.py migrate

# Исправить проблемы с миграциями (если есть)
python manage.py fix_migrations

# Создать суперпользователя (опционально)
python manage.py createsuperuser
```

**Или используйте автоматическую настройку:**
```bash
python setup.py
```

### 4. Заполнение тестовыми данными

```bash
# Заполнить базу тестовыми данными
python manage.py populate_db --clear --owners 10 --cats 20 --ratings 50

# Создать тестовые изображения
python manage.py create_test_images
```

### 5. Запуск сервера

```bash
# Запустить сервер разработки
python manage.py runserver
```

## 🌐 Доступные URL

### Веб-интерфейс
- **Главная страница**: http://127.0.0.1:8000/
- **Добавить владельца**: http://127.0.0.1:8000/add-owner/
- **Добавить кошку**: http://127.0.0.1:8000/add-cat/
- **Список кошек**: http://127.0.0.1:8000/list-cats/
- **Рейтинги**: http://127.0.0.1:8000/ratings/
- **Оценить котенка**: http://127.0.0.1:8000/add-rating/

### API и документация
- **Swagger UI**: http://127.0.0.1:8000/swagger/
- **ReDoc**: http://127.0.0.1:8000/redoc/
- **API Base**: http://127.0.0.1:8000/api/v1/

### Админ-панель
- **Django Admin**: http://127.0.0.1:8000/admin/

## 🔐 JWT Авторизация

### Регистрация пользователя
```bash
POST /api/v1/auth/register/
{
    "username": "user123",
    "email": "user@example.com",
    "password": "password123",
    "name": "Иван",
    "surname": "Иванов",
    "patronymic": "Иванович"
}
```

### Авторизация
```bash
POST /api/v1/auth/login/
{
    "username": "user123",
    "password": "password123"
}
```

### Использование токена
```bash
# Добавить в заголовок запроса
Authorization: Bearer <access_token>
```

## 📚 API Endpoints

### Кошки
- `GET /api/v1/cats/` - список всех кошек
- `POST /api/v1/cats/` - добавить кошку
- `GET /api/v1/cats/{id}/` - получить кошку
- `PUT /api/v1/cats/{id}/` - обновить кошку
- `DELETE /api/v1/cats/{id}/` - удалить кошку
- `GET /api/v1/cats/breeds/` - список пород
- `GET /api/v1/cats/top_rated/` - топ-10 кошек

### Владельцы
- `GET /api/v1/owners/` - список владельцев
- `POST /api/v1/owners/` - добавить владельца
- `GET /api/v1/owners/{id}/cats/` - кошки владельца

### Рейтинги
- `GET /api/v1/ratings/` - список рейтингов
- `POST /api/v1/ratings/` - добавить рейтинг
- `GET /api/v1/ratings/my_ratings/` - мои рейтинги

## 🛠️ Команды управления

### Заполнение тестовыми данными
```bash
# Базовое заполнение
python manage.py populate_db

# С настройками
python manage.py populate_db --owners 15 --cats 30 --ratings 100 --clear

# Создание изображений
python manage.py create_test_images --width 600 --height 400
```

### Миграции
```bash
# Создать миграции
python manage.py makemigrations

# Применить миграции
python manage.py migrate
```

### Статические файлы
```bash
# Собрать статические файлы
python manage.py collectstatic
```

## 📁 Структура проекта

```
workmate/
├── exhibition_app/
│   ├── management/
│   │   └── commands/
│   │       ├── populate_db.py
│   │       └── create_test_images.py
│   ├── templates/
│   │   └── exhibition_app/
│   │       ├── base.html
│   │       ├── home.html
│   │       ├── add_owner.html
│   │       ├── add_cat.html
│   │       ├── edit_cat.html
│   │       ├── list_cats.html
│   │       ├── add_rating.html
│   │       └── ratings.html
│   ├── static/
│   │   └── exhibition_app/
│   │       └── css/
│   │           └── style.css
│   ├── models.py
│   ├── views.py
│   ├── api_views.py
│   ├── jwt_views.py
│   ├── serializers.py
│   ├── urls.py
│   └── api_urls.py
├── workmate/
│   ├── settings.py
│   ├── urls.py
│   └── wsgi.py
├── requirements.txt
├── README.md
├── README_forms.md
├── README_rating_system.md
└── README_test_data.md
```

## 🔧 Настройки

### Основные настройки (settings.py)
- **База данных**: SQLite (по умолчанию)
- **Статические файлы**: настроены для разработки
- **Медиа файлы**: папка `cats/`
- **JWT токены**: 60 минут access, 1 день refresh

### Переменные окружения
Создайте файл `.env` в корне проекта:
```env
DEBUG=True
SECRET_KEY=your-secret-key
DATABASE_URL=sqlite:///db.sqlite3
```

## 🐛 Отладка

### Логи
```bash
# Запуск с подробными логами
python manage.py runserver --verbosity=2
```

### Проверка миграций
```bash
# Показать статус миграций
python manage.py showmigrations
```

### Проверка статических файлов
```bash
# Проверить статические файлы
python manage.py collectstatic --dry-run
```

## 📱 Мобильная поддержка

- Адаптивный дизайн для всех устройств
- API готов для мобильных приложений
- JWT токены для безопасной авторизации

## 🔒 Безопасность

- JWT токены с ограниченным временем жизни
- CSRF защита для веб-форм
- Валидация данных на уровне API
- Безопасная обработка файлов

## 🚀 Развертывание

### Для продакшена
1. Установить PostgreSQL или MySQL
2. Настроить переменные окружения
3. Собрать статические файлы
4. Настроить веб-сервер (nginx + gunicorn)

### Docker (опционально)
```bash
# Создать Dockerfile
docker build -t cat-exhibition .
docker run -p 8000:8000 cat-exhibition
```

## 📞 Поддержка

- **Документация API**: http://127.0.0.1:8000/swagger/
- **Исходный код**: доступен в репозитории
- **Issues**: создавайте в GitHub

## 📄 Лицензия

MIT License - свободное использование и модификация.

---

**Приятного использования! 🐱✨** 