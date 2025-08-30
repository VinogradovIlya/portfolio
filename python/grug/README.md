# drug

## [Содержание](#содержание)

1. [Backend](#backend)
2. [Frontend](#frontend)
3. [Databases](#databeses)
4. [Стурктура проeкта](#структура-проекта)
    - [accounts](#accounts)
        - [tests/](#tests)
        - [models.py](#modelspy)
        - [urls.py](#urlspy)
        - [views.py](#viewspy)
        - [services.py](#servicespy)
        - [selectors.py](#selectorspy)
        - [serializers.py](#serializerspy)
        - [admin.py](#adminpy)
    - [web](#web)
    - [config](#config)
5. [Запуск](#Запуск)
7. [Зависимости](#Зависимости)

## Backend

Backend часть проекта написана на Python с использованием Django, DRF

## Frontend

## Databeses

В проекте используется Django ORM + PostgreSQL

## Структура проекта

```
drug_backend/
├── manage.py                           # Django утилита командной строки
├── .env.example                        # пример переменных окружения
├── .gitignore                          # исключения для git
├── README.md                           # документация проекта
├── requirements/                       # зависимости Python
│   ├── base.txt                        # основные зависимости
│   ├── development.txt                 # зависимости для разработки
│   ├── production.txt                  # зависимости для продакшена
│   └── testing.txt                     # зависимости для тестов
├── config/                             # основные настройки Django проекта
│   ├── __init__.py
│   ├── urls.py                         # корневые URL паттерны
│   ├── wsgi.py                         # WSGI точка входа для продакшена
│   ├── asgi.py                         # ASGI точка входа для WebSocket/async
│   └── settings/                       # модульные настройки
│       ├── __init__.py
│       ├── base.py                     # общие настройки для всех окружений
│       ├── development.py              # настройки для разработки
│       ├── production.py               # настройки для продакшена
│       ├── testing.py                  # настройки для тестов
│       └── components/                 # компоненты настроек (БЕЗ __init__.py)
│           ├── apps.py                 # INSTALLED_APPS и конфигурация приложений
│           ├── database.py             # настройки базы данных
│           ├── drf.py                  # Django REST Framework настройки
│           ├── auth.py                 # аутентификация и авторизация
│           ├── media.py                # статические файлы и медиа
│           ├── logging.py              # настройки логирования
│           ├── cache.py                # настройки кэширования (Redis/Memcached)
│           ├── celery.py               # настройки для асинхронных задач
│           └── cors.py                 # CORS настройки для фронтенда
├── core/                               # общие компоненты для всего проекта
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения core
│   ├── models.py                       # абстрактные базовые модели
│   ├── utils.py                        # общие утилиты и хелперы
│   ├── permissions.py                  # кастомные права доступа
│   ├── constants.py                    # константы проекта
│   ├── exceptions.py                   # кастомные исключения
│   ├── validators.py                   # кастомные валидаторы
│   ├── pagination.py                   # кастомная пагинация
│   ├── middleware.py                   # кастомные middleware
│   └── management/                     # Django команды
│       ├── __init__.py
│       └── commands/
│           ├── __init__.py
│           └── populate_test_data.py   # команда для заполнения тестовых данных
├── accounts/                           # управление пользователями (B2C + B2B)
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения accounts
│   ├── models.py                       # модели User, Profile, etc.
│   ├── admin.py                        # настройки админки для пользователей
│   ├── urls.py                         # URL паттерны для accounts
│   ├── views.py                        # API views для аутентификации
│   ├── serializers.py                  # сериализаторы для API
│   ├── services.py                     # бизнес-логика регистрации/авторизации
│   ├── selectors.py                    # запросы для получения пользователей
│   ├── permissions.py                  # права доступа для accounts
│   ├── signals.py                      # Django сигналы для пользователей
│   ├── migrations/                     # миграции базы данных
│   │   └── __init__.py
│   └── tests/                          # тесты для accounts
│       ├── __init__.py
│       ├── test_models.py              # тесты моделей
│       ├── test_views.py               # тесты API views
│       ├── test_services.py            # тесты бизнес-логики
│       └── test_selectors.py           # тесты селекторов
├── pets/                               # питомцы и владельцы (B2C)
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения pets
│   ├── models.py                       # модели Pet, Owner, Breed, etc.
│   ├── admin.py                        # настройки админки для питомцев
│   ├── urls.py                         # URL паттерны для pets
│   ├── views.py                        # API views для управления питомцами
│   ├── serializers.py                  # сериализаторы для питомцев
│   ├── services.py                     # создание/обновление питомцев
│   ├── selectors.py                    # выборка питомцев с фильтрами
│   ├── filters.py                      # фильтры для поиска питомцев
│   ├── signals.py                      # сигналы для питомцев
│   ├── migrations/
│   │   └── __init__.py
│   └── tests/
│       ├── __init__.py
│       ├── test_models.py
│       ├── test_views.py
│       ├── test_services.py
│       └── test_selectors.py
├── medical/                            # медицинские записи и история
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения medical
│   ├── models.py                       # модели Vaccination, Treatment, MedicalRecord
│   ├── admin.py                        # админка для медицинских записей
│   ├── urls.py                         # URL паттерны для medical
│   ├── views.py                        # API для медицинских данных
│   ├── serializers.py                  # сериализаторы медицинских данных
│   ├── services.py                     # добавление прививок/процедур
│   ├── selectors.py                    # выборка медицинских данных
│   ├── filters.py                      # фильтры для медицинских записей
│   ├── signals.py                      # сигналы для медицинских событий
│   ├── migrations/
│   │   └── __init__.py
│   └── tests/
│       ├── __init__.py
│       ├── test_models.py
│       ├── test_views.py
│       ├── test_services.py
│       └── test_selectors.py
├── clinics/                            # ветеринарные клиники (B2B)
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения clinics
│   ├── models.py                       # модели Clinic, Service, Doctor, Schedule
│   ├── admin.py                        # админка для клиник
│   ├── urls.py                         # URL паттерны для clinics
│   ├── views.py                        # API для управления клиниками
│   ├── serializers.py                  # сериализаторы для клиник
│   ├── services.py                     # управление услугами клиники
│   ├── selectors.py                    # поиск клиник и услуг
│   ├── filters.py                      # фильтры для поиска клиник
│   ├── permissions.py                  # права доступа для клиник
│   ├── signals.py                      # сигналы для клиник
│   ├── migrations/
│   │   └── __init__.py
│   └── tests/
│       ├── __init__.py
│       ├── test_models.py
│       ├── test_views.py
│       ├── test_services.py
│       └── test_selectors.py
├── marketplace/                        # маркетплейс товаров и услуг (B2B → B2C)
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения marketplace
│   ├── models.py                       # модели Product, Order, Cart, Booking
│   ├── admin.py                        # админка для маркетплейса
│   ├── urls.py                         # URL паттерны для marketplace
│   ├── views.py                        # API для покупок и бронирований
│   ├── serializers.py                  # сериализаторы для маркетплейса
│   ├── services.py                     # создание заказов, покупки, бронирование
│   ├── selectors.py                    # поиск товаров/услуг
│   ├── filters.py                      # фильтры для товаров и услуг
│   ├── permissions.py                  # права доступа для маркетплейса
│   ├── signals.py                      # сигналы для заказов
│   ├── tasks.py                        # асинхронные задачи (уведомления, платежи)
│   ├── migrations/
│   │   └── __init__.py
│   └── tests/
│       ├── __init__.py
│       ├── test_models.py
│       ├── test_views.py
│       ├── test_services.py
│       └── test_selectors.py
├── notifications/                      # система уведомлений
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения notifications
│   ├── models.py                       # модели Notification, EmailTemplate
│   ├── admin.py                        # админка для уведомлений
│   ├── urls.py                         # URL паттерны для notifications
│   ├── views.py                        # API для уведомлений
│   ├── serializers.py                  # сериализаторы для уведомлений
│   ├── services.py                     # отправка уведомлений
│   ├── selectors.py                    # получение уведомлений
│   ├── tasks.py                        # асинхронная отправка уведомлений
│   ├── migrations/
│   │   └── __init__.py
│   └── tests/
│       ├── __init__.py
│       ├── test_models.py
│       ├── test_views.py
│       ├── test_services.py
│       └── test_tasks.py
├── frontend/                           # веб-интерфейс (если есть)
│   ├── __init__.py
│   ├── apps.py                         # конфигурация приложения frontend
│   ├── urls.py                         # URL для веб-страниц
│   ├── views.py                        # веб-представления
│   ├── templates/                      # HTML шаблоны
│   │   ├── base.html
│   │   ├── index.html
│   │   └── registration/
│   │       ├── login.html
│   │       └── register.html
│   └── static/                         # статические файлы
│       ├── css/
│       ├── js/
│       └── images/
├── media/                              # загружаемые пользователями файлы
│   ├── pets/                           # фотографии питомцев
│   ├── clinics/                        # фотографии клиник
│   └── products/                       # фотографии товаров
├── static/                             # статические файлы проекта
│   ├── admin/                          # админка Django
│   ├── rest_framework/                 # DRF статика
│   └── css/
├── locale/                             # файлы переводов (i18n)
│   ├── en/
│   └── ru/
├── docs/                               # документация проекта
│   ├── api.md                          # описание API
│   ├── deployment.md                   # инструкции по деплою
│   └── database.md                     # схема базы данных
├── scripts/                            # вспомогательные скрипты
│   ├── deploy.sh                       # скрипт деплоя
│   ├── backup.sh                       # скрипт бэкапа БД
│   └── seed_data.py                    # заполнение тестовых данных
├── docker/                             # Docker конфигурация
│   ├── Dockerfile
│   ├── docker-compose.yml
│   ├── docker-compose.prod.yml
│   └── nginx/
│       └── nginx.conf
└── logs/                               # файлы логов (в .gitignore)
    ├── django.log
    └── celery.log
```

### accounts

#### [tests/](#tests)

Папка с тестами для API покрытыми pytest

#### models.py

Файл для db

#### urls.py

Наши пути для API

#### views.py

Файл с логикой API

#### services.py

Вспомогательная логика для [views.py](#viewspy)

#### selectors.py

Селекторы нашего API (Вспомогательная логика для [views.py](#viewspy))

#### serializers.py

Сериализаторы нашего API

#### admin.py

admin панель для нашего API (пока пусто)

### config/

Основная папка проекта, в которой находятся настройки проекта, пути для API, web

### web

Папка с представлениями для нашего сайта, который использует наш API

### Запуск

Для запуска проекта был создан Makefile, в котором есть цели для тестирования и отчета

### Зависимости

Список используемых Python инструментов находится в файле requirements.txt
