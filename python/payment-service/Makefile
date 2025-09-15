.PHONY: help build up down restart logs clean test lint format migrate rebuild typecheck check fix env test-simple test-auth test-payments

COMPOSE_FILE = docker-compose.yml
SERVICE_WEB = web
SERVICE_DB = db

help:
	@echo "Доступные команды:"
	@echo "  rebuild   - Универсальная команда: очистить все + собрать + запустить + миграции"
	@echo "  up        - Запустить все сервисы (если уже собраны)"
	@echo "  down      - Остановить все сервисы"
	@echo "  logs      - Показать логи"
	@echo "  logs-web  - Показать логи веб-сервиса"
	@echo "  logs-db   - Показать логи базы данных"
	@echo "  shell     - Подключиться к контейнеру приложения"
	@echo "  db-shell  - Подключиться к PostgreSQL"
	@echo "  test      - Запустить все тесты"
	@echo "  test-simple    - Запустить только простые тесты"
	@echo "  test-auth      - Запустить тесты аутентификации"
	@echo "  test-payments  - Запустить тесты платежей"
	@echo "  format    - Отформатировать код"
	@echo "  lint      - Проверить стиль кода"
	@echo "  typecheck - Проверить типы (mypy)"
	@echo "  check     - Полная проверка качества кода"

rebuild:
	@echo "🧹 Очищаем все..."
	docker-compose -f $(COMPOSE_FILE) down -v --remove-orphans
	docker system prune -f
	docker volume prune -f
	@echo "🔨 Собираем образы без кэша..."
	docker-compose -f $(COMPOSE_FILE) build --no-cache
	@echo "🚀 Запускаем сервисы..."
	docker-compose -f $(COMPOSE_FILE) up -d
	@echo "⏳ Ждем готовности базы данных..."
	sleep 10
	@echo "📊 Создаем миграции..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) rm -f alembic/versions/*.py || true
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) alembic revision --autogenerate -m "Initial migration" || true
	@echo "🗃️ Применяем миграции..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) alembic upgrade head || true
	@echo ""
	@echo "✅ Готово! Приложение доступно:"
	@echo "   📖 API документация: http://localhost:8000/docs"
	@echo "   🏠 Главная страница: http://localhost:8000"
	@echo "   📊 Статус: http://localhost:8000/health"
	@echo ""

up:
	docker-compose -f $(COMPOSE_FILE) up -d

down:
	docker-compose -f $(COMPOSE_FILE) down

restart: down up

logs:
	docker-compose -f $(COMPOSE_FILE) logs -f

logs-web:
	docker-compose -f $(COMPOSE_FILE) logs -f $(SERVICE_WEB)

logs-db:
	docker-compose -f $(COMPOSE_FILE) logs -f $(SERVICE_DB)

shell:
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) /bin/bash

db-shell:
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_DB) psql -U user -d payment_db

test:
	@echo "🧪 Запускаем все тесты..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) pytest -v --tb=short

test-coverage:
    pytest --cov=app --cov-report=html --cov-report=term

test-simple:
	@echo "🧪 Запускаем простые тесты..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) pytest tests/test_simple.py tests/test_main.py -v

test-auth:
	@echo "🧪 Запускаем тесты аутентификации..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) pytest tests/test_auth.py -v

test-payments:
	@echo "🧪 Запускаем тесты платежей..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) pytest tests/test_payments.py -v

test-working:
	@echo "🧪 Запускаем рабочие тесты..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) pytest tests/test_working.py -v

status:
	docker-compose -f $(COMPOSE_FILE) ps

format:
	black app/ tests/ alembic/
	isort app/ tests/ alembic/
	autopep8 --in-place --aggressive --recursive app/ tests/ alembic/
	@echo "Код отформатирован!"

lint:
	flake8 app/ tests/ alembic/
	black --check app/ tests/ alembic/
	isort --check-only app/ tests/ alembic/
	@echo "Стиль кода проверен!"

typecheck:
	mypy app/ || echo "Mypy проверка завершена (могут быть предупреждения)"

check: format lint #typecheck
	@echo "Все проверки завершены!"

env:
	cp .env.example .env
	@echo ".env файл создан. Отредактируйте его при необходимости."

debug-test:
	@echo "🐛 Отладка тестов..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) pytest -v -s --tb=long

clean-test:
	@echo "🧹 Очистка тестовых данных..."
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) find . -name "*.pyc" -delete
	docker-compose -f $(COMPOSE_FILE) exec $(SERVICE_WEB) find . -name "__pycache__" -type d -exec rm -rf {} + || true
