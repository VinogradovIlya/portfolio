# Payment Service API

Сервис для создания и управления платежами на базе FastAPI с PostgreSQL.

## Возможности

- 🔐 JWT аутентификация
- 💰 Создание и управление платежами
- 🏦 Автоматическое списание/зачисление средств
- 📊 API документация (Swagger UI)
- 🐳 Docker контейнеризация
- 🗃️ Миграции базы данных (Alembic)
- ✅ Автоматические тесты
- 🎨 Форматирование кода (Black, isort)
- 📝 Логирование операций

## Быстрый старт

1. **Клонируйте репозиторий:**

```bash
git clone git@github.com:VinogradovIlya/payment-service.git
cd payment-service
```

2. **Создайте .env файл:**

```bash
make env
```

3. **Запустите проект:**

```bash
make dev
```

4. **Создайте и примените миграции:**

```bash
make init-migrations
make migrate
```

5. **Откройте API документацию:**
   - Swagger UI: <http://localhost:8000/docs>
   - ReDoc: <http://localhost:8000/redoc>

## API Endpoints

### Аутентификация

- `POST /auth/register` - Регистрация пользователя
- `POST /auth/login` - Вход пользователя
- `GET /auth/me` - Информация о текущем пользователе

### Платежи

- `POST /payments/` - Создание платежа
- `GET /payments/` - Список платежей пользователя
- `GET /payments/{id}` - Информация о платеже
- `PUT /payments/{id}/confirm` - Подтверждение платежа
- `PUT /payments/{id}/cancel` - Отмена платежа

### Системные

- `GET /` - Корневая страница
- `GET /health` - Проверка здоровья сервиса

## Команды Make

### Основные команды

- `make dev` - Запуск в режиме разработки
- `make up` - Запуск сервисов
- `make down` - Остановка сервисов
- `make restart` - Перезапуск
- `make logs` - Просмотр логов
- `make shell` - Подключение к контейнеру

### База данных

- `make init-migrations` - Создание первоначальных миграций
- `make migration` - Создание новой миграции
- `make migrate` - Применение миграций
- `make db-shell` - Подключение к PostgreSQL

### Качество кода

- `make format` - Форматирование кода
- `make lint` - Проверка стиля
- `make typecheck` - Проверка типов
- `make check` - Полная проверка
- `make test` - Запуск тестов

## Ветки

- **main** - стабильная версия для production
- **develop** - ветка разработки для новых фич
- Для новых возможностей создавайте feature/* ветки

Ветки:
├── main (stable, production-ready) ✅
├── develop (development, latest features) ✅
└── [feature branches при необходимости]

Tags:
└── v1.0.0

## Тестирование API

### 1. Регистрация пользователя

```bash
curl -X POST "http://localhost:8000/auth/register" \
  -H "Content-Type: application/json" \
  -d '{
    "email": "user@example.com",
    "username": "testuser",
    "password": "password123",
    "full_name": "Test User"
  }'
```

### 2. Вход в систему

```bash
curl -X POST "http://localhost:8000/auth/login" \
  -H "Content-Type: application/json" \
  -d '{
    "username": "testuser",
    "password": "password123"
  }'
```

### 3. Создание платежа (с токеном)

```bash
curl -X POST "http://localhost:8000/payments/" \
  -H "Authorization: Bearer YOUR_TOKEN_HERE" \
  -H "Content-Type: application/json" \
  -d '{
    "amount": 100.50,
    "description": "Test payment",
    "card_last_four": "1234",
    "card_holder_name": "John Doe"
  }'
```

## Архитектура проекта

```
payment-service/
├── app/
│   ├── core/          # Конфигурация, БД, безопасность
│   ├── models/        # SQLAlchemy модели
│   ├── schemas/       # Pydantic схемы
│   ├── routers/       # FastAPI роутеры
│   ├── services/      # Бизнес-логика
│   ├── utils/         # Утилиты
│   └── main.py        # Главный файл приложения
├── alembic/           # Миграции БД
├── tests/             # Тесты
├── docker-compose.yml # Docker конфигурация
└── requirements.txt   # Python зависимости
```

## Переменные окружения

```bash
# База данных
DATABASE_URL=postgresql+asyncpg://user:password@db:5432/payment_db
POSTGRES_DB=payment_db
POSTGRES_USER=user
POSTGRES_PASSWORD=password

# Безопасность
SECRET_KEY=your-super-secret-key-change-this-in-production
ALGORITHM=HS256
ACCESS_TOKEN_EXPIRE_MINUTES=30

# Приложение
DEBUG=True
HOST=0.0.0.0
PORT=8000
```

## Технологии

- **FastAPI** - современный веб-фреймворк для Python
- **PostgreSQL** - реляционная база данных
- **SQLAlchemy** - ORM для работы с БД
- **Alembic** - миграции базы данных
- **Pydantic** - валидация данных
- **JWT** - аутентификация
- **Docker** - контейнеризация
- **pytest** - тестирование

## Разработка

### Установка pre-commit хуков

```bash
make pre-commit-install
```

### Запуск тестов

```bash
make test
```

### Проверка кода

```bash
make check
```
