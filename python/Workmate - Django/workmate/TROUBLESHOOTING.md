# Устранение проблем - Выставка кошек

## 🔧 Проблемы с миграциями

### Ошибка: "No migrations to apply"
```bash
# Проверьте статус миграций
python manage.py showmigrations

# Если есть непримененные миграции, примените их
python manage.py migrate
```

### Ошибка: "Table doesn't exist"
```bash
# Сбросьте базу данных и создайте заново
python manage.py fix_migrations --reset

# Или вручную:
rm db.sqlite3
python manage.py makemigrations
python manage.py migrate
```

### Ошибка с token_blacklist
```bash
# Примените миграции для JWT
python manage.py migrate token_blacklist

# Или примените все миграции
python manage.py migrate
```

## 🐍 Проблемы с Python

### Ошибка: "python: command not found"
```bash
# Установите Python 3.8+ или используйте python3
python3 manage.py migrate

# Или создайте виртуальное окружение
python3 -m venv venv
source venv/bin/activate  # macOS/Linux
venv\Scripts\activate     # Windows
```

### Ошибка версии Python
```bash
# Проверьте версию
python --version

# Требуется Python 3.8 или выше
```

## 📦 Проблемы с зависимостями

### Ошибка: "ModuleNotFoundError"
```bash
# Установите зависимости
pip install -r requirements.txt

# Или обновите pip
pip install --upgrade pip
pip install -r requirements.txt
```

### Ошибка с Pillow
```bash
# На macOS может потребоваться
brew install libjpeg zlib

# На Ubuntu/Debian
sudo apt-get install python3-dev python3-pip libjpeg-dev zlib1g-dev

# Затем установите Pillow
pip install Pillow
```

## 🗄️ Проблемы с базой данных

### Ошибка: "database is locked"
```bash
# Остановите сервер и попробуйте снова
# Или перезапустите терминал
```

### Ошибка: "no such table"
```bash
# Создайте миграции заново
python manage.py makemigrations exhibition_app
python manage.py migrate
```

## 🌐 Проблемы с сервером

### Ошибка: "Address already in use"
```bash
# Найдите процесс на порту 8000
lsof -i :8000

# Остановите процесс
kill -9 <PID>

# Или используйте другой порт
python manage.py runserver 8001
```

### Ошибка: "Permission denied"
```bash
# Проверьте права доступа к файлам
chmod +x manage.py
chmod +x setup.py
```

## 📁 Проблемы с файлами

### Ошибка: "static files not found"
```bash
# Соберите статические файлы
python manage.py collectstatic

# Проверьте настройки в settings.py
```

### Ошибка: "media files not found"
```bash
# Создайте директории для медиа файлов
mkdir -p media/cats
mkdir -p staticfiles
```

## 🔐 Проблемы с JWT

### Ошибка: "Invalid token"
```bash
# Проверьте настройки JWT в settings.py
# Убедитесь, что SECRET_KEY установлен
```

### Ошибка: "Token has expired"
```bash
# Обновите токен
POST /api/v1/auth/token/refresh/
{
    "refresh": "your_refresh_token"
}
```

## 🚀 Автоматическое исправление

### Используйте скрипт настройки
```bash
# Полная автоматическая настройка
python setup.py

# Или пошагово
python manage.py fix_migrations
python manage.py populate_db --clear
python manage.py create_test_images
```

## 📋 Проверка работоспособности

### Тест 1: Проверка миграций
```bash
python manage.py showmigrations
# Все миграции должны быть отмечены [X]
```

### Тест 2: Проверка сервера
```bash
python manage.py runserver
# Сервер должен запуститься без ошибок
```

### Тест 3: Проверка API
```bash
# Откройте в браузере
http://127.0.0.1:8000/swagger/
# Должна загрузиться документация Swagger
```

### Тест 4: Проверка веб-интерфейса
```bash
# Откройте в браузере
http://127.0.0.1:8000/
# Должна загрузиться главная страница
```

## 🆘 Если ничего не помогает

### Полный сброс проекта
```bash
# Удалите базу данных и миграции
rm db.sqlite3
rm -rf exhibition_app/migrations/0*.py

# Переустановите зависимости
pip uninstall -r requirements.txt -y
pip install -r requirements.txt

# Создайте все заново
python manage.py makemigrations
python manage.py migrate
python manage.py populate_db --clear
```

### Проверьте логи
```bash
# Запустите сервер с подробными логами
python manage.py runserver --verbosity=2
```

## 📞 Получение помощи

1. **Проверьте документацию**: README.md
2. **Посмотрите логи**: вывод команд
3. **Проверьте настройки**: settings.py
4. **Создайте issue**: в репозитории проекта

## 🔍 Частые проблемы

### Проблема: "ImportError: No module named 'rest_framework'"
**Решение:**
```bash
pip install djangorestframework
```

### Проблема: "ImportError: No module named 'drf_yasg'"
**Решение:**
```bash
pip install drf-yasg
```

### Проблема: "ImportError: No module named 'PIL'"
**Решение:**
```bash
pip install Pillow
```

### Проблема: "django.db.utils.OperationalError: no such table"
**Решение:**
```bash
python manage.py migrate --run-syncdb
```

---

**💡 Совет:** Если проблема не решается, попробуйте использовать автоматический скрипт настройки `python setup.py` 