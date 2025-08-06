# API Документация - Выставка кошек

## 🔗 Ссылки на API

- **Swagger UI**: http://127.0.0.1:8000/swagger/
- **ReDoc**: http://127.0.0.1:8000/redoc/
- **API Base URL**: http://127.0.0.1:8000/api/v1/

## 🔐 JWT Авторизация

### Регистрация пользователя
```http
POST /api/v1/auth/register/
Content-Type: application/json

{
    "username": "user123",
    "email": "user@example.com",
    "password": "password123",
    "name": "Иван",
    "surname": "Иванов",
    "patronymic": "Иванович"
}
```

**Ответ:**
```json
{
    "message": "Пользователь успешно зарегистрирован",
    "user": {
        "id": 1,
        "username": "user123",
        "email": "user@example.com"
    },
    "owner": {
        "id": 1,
        "name": "Иван",
        "surname": "Иванов",
        "patronymic": "Иванович"
    },
    "tokens": {
        "refresh": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9...",
        "access": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9..."
    }
}
```

### Авторизация
```http
POST /api/v1/auth/login/
Content-Type: application/json

{
    "username": "user123",
    "password": "password123"
}
```

**Ответ:**
```json
{
    "message": "Успешная авторизация",
    "user": {
        "id": 1,
        "username": "user123",
        "email": "user@example.com"
    },
    "owner": {
        "id": 1,
        "name": "Иван",
        "surname": "Иванов",
        "patronymic": "Иванович"
    },
    "tokens": {
        "refresh": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9...",
        "access": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9..."
    }
}
```

### Обновление токена
```http
POST /api/v1/auth/token/refresh/
Content-Type: application/json

{
    "refresh": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9..."
}
```

### Выход из системы
```http
POST /api/v1/auth/logout/
Authorization: Bearer <access_token>
Content-Type: application/json

{
    "refresh_token": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9..."
}
```

### Получение профиля
```http
GET /api/v1/auth/profile/
Authorization: Bearer <access_token>
```

## 🐱 API Кошек

### Получить список всех кошек
```http
GET /api/v1/cats/
Authorization: Bearer <access_token>
```

**Параметры запроса:**
- `breed` - фильтр по породе
- `min_age` - минимальный возраст (месяцы)
- `max_age` - максимальный возраст (месяцы)
- `sort_by` - сортировка (`rating`, `age`, `breed`)

**Пример:**
```http
GET /api/v1/cats/?breed=Сиамская&min_age=6&sort_by=rating
```

**Ответ:**
```json
{
    "count": 5,
    "next": null,
    "previous": null,
    "results": [
        {
            "id": 1,
            "colors": "Белый",
            "mounts": 12,
            "kitten_breed": "Сиамская",
            "description": "Очень ласковый и игривый котенок",
            "photo": "/cats/cat_1_siamskaya.jpg",
            "kitten_owner": {
                "id": 1,
                "name": "Иван",
                "surname": "Иванов",
                "patronymic": "Иванович"
            },
            "average_rating": 4.5,
            "ratings_count": 3
        }
    ]
}
```

### Получить конкретную кошку
```http
GET /api/v1/cats/{id}/
Authorization: Bearer <access_token>
```

### Добавить кошку
```http
POST /api/v1/cats/
Authorization: Bearer <access_token>
Content-Type: multipart/form-data

{
    "colors": "Черный",
    "mounts": 8,
    "kitten_breed": "Мейн-кун",
    "description": "Большой и пушистый котенок",
    "photo": <file>,
    "kitten_owner": 1
}
```

### Обновить кошку
```http
PUT /api/v1/cats/{id}/
Authorization: Bearer <access_token>
Content-Type: multipart/form-data

{
    "colors": "Серый",
    "mounts": 10,
    "kitten_breed": "Мейн-кун",
    "description": "Обновленное описание",
    "photo": <file>,
    "kitten_owner": 1
}
```

### Удалить кошку
```http
DELETE /api/v1/cats/{id}/
Authorization: Bearer <access_token>
```

### Получить рейтинги кошки
```http
GET /api/v1/cats/{id}/ratings/
Authorization: Bearer <access_token>
```

### Получить список пород
```http
GET /api/v1/cats/breeds/
Authorization: Bearer <access_token>
```

**Ответ:**
```json
[
    "Сиамская",
    "Персидская",
    "Мейн-кун",
    "Британская короткошерстная"
]
```

### Получить топ-10 кошек по рейтингу
```http
GET /api/v1/cats/top_rated/
Authorization: Bearer <access_token>
```

## 👥 API Владельцев

### Получить список владельцев
```http
GET /api/v1/owners/
Authorization: Bearer <access_token>
```

### Получить конкретного владельца
```http
GET /api/v1/owners/{id}/
Authorization: Bearer <access_token>
```

### Добавить владельца
```http
POST /api/v1/owners/
Authorization: Bearer <access_token>
Content-Type: application/json

{
    "name": "Мария",
    "surname": "Петрова",
    "patronymic": "Сергеевна"
}
```

### Получить кошек владельца
```http
GET /api/v1/owners/{id}/cats/
Authorization: Bearer <access_token>
```

## ⭐ API Рейтингов

### Получить список рейтингов
```http
GET /api/v1/ratings/
Authorization: Bearer <access_token>
```

### Добавить рейтинг
```http
POST /api/v1/ratings/
Authorization: Bearer <access_token>
Content-Type: application/json

{
    "cat": 1,
    "author": 1,
    "rating": 5
}
```

**Примечание:** Если рейтинг от этого автора уже существует, он будет обновлен.

### Получить мои рейтинги
```http
GET /api/v1/ratings/my_ratings/
Authorization: Bearer <access_token>
```

## 🖼️ API Изображений

### Получить список изображений
```http
GET /api/v1/images/
Authorization: Bearer <access_token>
```

### Добавить изображение
```http
POST /api/v1/images/
Authorization: Bearer <access_token>
Content-Type: multipart/form-data

{
    "cat_photo": 1,
    "author": 1
}
```

## 📊 Примеры использования

### Получение кошек с фильтрацией
```bash
curl -X GET "http://127.0.0.1:8000/api/v1/cats/?breed=Сиамская&min_age=6" \
  -H "Authorization: Bearer <access_token>"
```

### Добавление рейтинга
```bash
curl -X POST "http://127.0.0.1:8000/api/v1/ratings/" \
  -H "Authorization: Bearer <access_token>" \
  -H "Content-Type: application/json" \
  -d '{
    "cat": 1,
    "author": 1,
    "rating": 5
  }'
```

### Загрузка изображения
```bash
curl -X POST "http://127.0.0.1:8000/api/v1/cats/" \
  -H "Authorization: Bearer <access_token>" \
  -F "colors=Черный" \
  -F "mounts=8" \
  -F "kitten_breed=Мейн-кун" \
  -F "description=Красивый котенок" \
  -F "photo=@cat_photo.jpg" \
  -F "kitten_owner=1"
```

## 🔧 Коды ответов

- `200 OK` - успешный запрос
- `201 Created` - ресурс создан
- `400 Bad Request` - неверные данные
- `401 Unauthorized` - не авторизован
- `403 Forbidden` - нет прав доступа
- `404 Not Found` - ресурс не найден
- `500 Internal Server Error` - ошибка сервера

## 📝 Примечания

1. **Авторизация**: Все API endpoints (кроме auth) требуют JWT токен
2. **Файлы**: Для загрузки изображений используйте `multipart/form-data`
3. **Пагинация**: Списки возвращаются с пагинацией (20 элементов на страницу)
4. **Фильтрация**: Поддерживается фильтрация по породе и возрасту
5. **Сортировка**: Доступна сортировка по рейтингу, возрасту и породе

## 🚀 Интеграция с мобильными приложениями

API полностью готов для интеграции с мобильными приложениями:

- JWT токены для безопасной авторизации
- JSON ответы
- Поддержка загрузки файлов
- Стандартные HTTP коды ответов
- Документация в формате OpenAPI/Swagger

Для получения полной документации с интерактивными примерами посетите:
**http://127.0.0.1:8000/swagger/** 