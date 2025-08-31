# PostgreSQL Portfolio - Проекты работы с базами данных

![PostgreSQL](https://img.shields.io/badge/PostgreSQL-316192?style=for-the-badge&logo=postgresql&logoColor=white)
![SQL](https://img.shields.io/badge/SQL-4479A1?style=for-the-badge&logo=sql&logoColor=white)
![Database](https://img.shields.io/badge/Database-Design-orange?style=for-the-badge)

## 🤝 Контакты

- **Email**: <vivpost@mail.ru>
<!-- - **LinkedIn**: [Ваш профиль](https://linkedin.com/in/yourprofile) -->
- **GitHub**: [Мой профиль](https://github.com/VinogradovIlya)
- **Telegram**: @vivpost

## 🎓 Области экспертизы

- **E-commerce**: система пиццерий с заказами, меню, посещениями
- **Системы учета**: персональные скидки, аудит изменений данных
- **Аналитические системы**: агрегация данных, отчетность
- **Алгоритмические задачи**: задача коммивояжера средствами SQL

## 📈 Результаты проектов

- ✅ **12 модулей** продвинутого SQL и PostgreSQL
- ✅ **80+ практических упражнений** с реальными задачами
- ✅ **Работа с транзакциями** и уровнями изоляции
- ✅ **Создание функций и триггеров** для автоматизации
- ✅ **Решение алгоритмических задач** средствами SQL

## 📋 Содержание

- [Описание проекта](#описание-проекта)
- [Структура портфолио](#структура-портфолио)
- [Технические компетенции](#технические-компетенции)
- [Ключевые проекты](#ключевые-проекты)
- [Установка и запуск](#установка-и-запуск)
- [Примеры кода](#примеры-кода)

## 🎯 Описание проекта

Коллекция проектов, демонстрирующая навыки работы с PostgreSQL и управления базами данных. Портфолио охватывает различные аспекты работы с СУБД: от базовых запросов до создания функций, триггеров и решения сложных алгоритмических задач.

## 🗂️ Структура портфолио

```
PostgreSQL/
├── SQLB1_Basic/                    # Основы SQL: SELECT, WHERE, CASE
├── SQLB2_Retrieving data/          # UNION, INTERSECT, EXCEPT, JOIN
├── SQLB3_Retrieving data/          # Сложные JOIN, подзапросы
├── SQLB4_DML/                      # INSERT, UPDATE, DELETE
├── SQLB5_Snapshots/                # VIEW, MATERIALIZED VIEW
├── SQLB6_Salesman problem/         # Задача коммивояжера с рекурсией
├── SQLB7_Database index/           # Создание и использование индексов
├── SQLB8_Integration features/     # Ограничения, последовательности
├── SQLB9_OLAP/                     # Группировка и агрегация
├── SQLB10_Isolation level/         # Уровни изоляции транзакций
├── SQLB11_Functions and procs/     # PL/pgSQL функции и триггеры
└── SQLB12_Warehouse fundamentals/  # Основы хранилищ данных
```

## 🛠️ Технические компетенции

### Основные технологии

- **PostgreSQL** - создание таблиц, ограничений, индексов
- **SQL** - SELECT, INSERT, UPDATE, DELETE, JOIN, подзапросы
- **PL/pgSQL** - функции, триггеры, условная логика

### Продемонстрированные навыки

- **EXPLAIN ANALYZE** - анализ планов выполнения запросов
- **Транзакции** - работа с уровнями изоляции, блокировками
- **Индексы** - B-tree, уникальные, составные, частичные индексы
- **Представления** - обычные и материализованные представления

## 🏗️ Ключевые проекты

### 1. Система управления пиццериями

- Создание связанной базы данных (person, pizzeria, menu, orders, visits)
- Работа с внешними ключами и ограничениями целостности
- Сложные многотабличные JOIN запросы

### 2. Уровни изоляции транзакций  

- Демонстрация аномалий: Lost Update, Non-Repeatable Reads, Phantom Reads
- Работа с различными уровнями изоляции (READ COMMITTED, REPEATABLE READ, SERIALIZABLE)
- Обработка взаимных блокировок (deadlock)

### 3. Функции и триггеры

- Создание PL/pgSQL функций для бизнес-логики
- Система аудита с автоматическими триггерами
- Функции для работы с массивами и вычислений

### 4. Задача коммивояжера

- Решение алгоритмической задачи с помощью рекурсивных CTE
- Поиск оптимального и наихудшего маршрута
- Работа с графами в SQL

### 5. Система индексирования

- Создание индексов для внешних ключей  
- Функциональные индексы (например, UPPER(name))
- Составные индексы для сложных запросов
- Уникальные и частичные индексы

## 🚀 Установка и запуск

### Требования

- PostgreSQL 12+
- Любой SQL-клиент (psql, pgAdmin, DBeaver)

### Запуск проектов

1. Клонируйте репозиторий:

```bash
git clone https://github.com/yourusername/postgresql-portfolio.git
cd postgresql-portfolio
```

2. Создайте базу данных:

```sql
CREATE DATABASE portfolio_db;
```

3. Примените схему данных:

```bash
psql -d portfolio_db -f PostgreSQL/SQLB1_Basic/materials/model.sql
```

4. Запустите любой проект:

```bash
psql -d portfolio_db -f PostgreSQL/SQLB1_Basic/src/ex00/day00_ex00.sql
```

## 💡 Примеры кода

### Использование ROW_NUMBER() для генерации ID

```sql
INSERT INTO person_discounts
SELECT ROW_NUMBER() OVER() as id,
       po.person_id,
       m.pizzeria_id,
       CASE
           WHEN count(*) = 1 THEN 10.5
           WHEN count(*) = 2 THEN 22
           ELSE 30
       END as discount
FROM person_order po
JOIN menu m ON po.menu_id = m.id
GROUP BY po.person_id, m.pizzeria_id;
```

### Рекурсивный CTE для задачи коммивояжера

```sql
WITH RECURSIVE tours AS (
    SELECT point1 AS tour, point1, point2, cost AS summa
    FROM nodes
    WHERE point1 = 'a'
    
    UNION ALL
    
    SELECT 
        (previous.tour || ',' || current.point1) AS trace,
        current.point1,
        current.point2,
        previous.summa + current.cost AS summa
    FROM nodes AS current
    INNER JOIN tours AS previous ON current.point1 = previous.point2
    WHERE tour NOT LIKE ('%' || current.point1 || '%')
)
SELECT summa AS total_cost, 
       ('{' || tour || ',' || point2 || '}') AS tour
FROM tours
WHERE LENGTH(tour) = LENGTH('a,c,d,b') AND point2 = 'a';
```

### Создание составного индекса

```sql
CREATE INDEX idx_person_order_multi 
ON person_order(person_id, menu_id, order_date);

-- Проверка использования индекса
EXPLAIN ANALYZE
SELECT person_id, menu_id, order_date
FROM person_order
WHERE person_id = 8 AND menu_id = 19;
```

### Триггер для системы аудита

```sql
CREATE OR REPLACE FUNCTION fnc_trg_person_audit() 
RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' THEN
        INSERT INTO person_audit (type_event, row_id, name, age, gender, address)
        VALUES ('I', NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
        RETURN NEW;
    ELSIF TG_OP = 'UPDATE' THEN
        INSERT INTO person_audit (type_event, row_id, name, age, gender, address)
        VALUES ('U', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
        RETURN NEW;
    ELSIF TG_OP = 'DELETE' THEN
        INSERT INTO person_audit (type_event, row_id, name, age, gender, address)
        VALUES ('D', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
        RETURN OLD;
    END IF;
END;
$$ LANGUAGE plpgsql;
```

### Сложные аналитические запросы

```sql
-- Сравнение посещений и заказов по ресторанам
WITH visits AS (
    SELECT pizzeria.name, COUNT(*) as visit_count
    FROM person_visits
    JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
    GROUP BY pizzeria.name
),
orders AS (
    SELECT pizzeria.name, COUNT(*) as order_count
    FROM person_order
    JOIN menu ON menu.id = person_order.menu_id
    JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    GROUP BY pizzeria.name
)
SELECT 
    COALESCE(v.name, o.name) as name,
    COALESCE(v.visit_count, 0) + COALESCE(o.order_count, 0) as total_count
FROM visits v
FULL OUTER JOIN orders o ON v.name = o.name
ORDER BY total_count DESC, name ASC;
```

---

⭐ **Понравился проект? Поставьте звездочку!**

*Данное портфолио демонстрирует практические навыки работы с PostgreSQL и готовность к решению реальных задач в области баз данных.*
