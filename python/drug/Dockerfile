FROM python:3.11-slim

WORKDIR /app

# Установка системных зависимостей для psycopg2 и TgCrypto
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    libpq-dev \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt .

# Обновляем pip и устанавливаем зависимости
RUN pip install --upgrade pip
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

# Создаем папки для статики и медиа
RUN mkdir -p /app/static /app/media

EXPOSE 8000

CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]

# # Запустить все сервисы
# docker-compose up

# # Запустить в фоне
# docker-compose up -d

# # Остановить
# docker-compose down

# # Посмотреть логи
# docker-compose logs web

# # Выполнить команду в контейнере
# docker-compose exec web python manage.py migrate

# # Пересобрать образы
# docker-compose build

# # Перезапустить конкретный сервис
# docker-compose restart web

# # 1. Разработка локально
# docker-compose up

# # 2. Внесли изменения в код
# docker-compose restart web

# # 3. Добавили новую библиотеку
# docker-compose build web
# docker-compose up

# # 4. Деплой на сервер
# docker-compose -f docker-compose.prod.yml up -d