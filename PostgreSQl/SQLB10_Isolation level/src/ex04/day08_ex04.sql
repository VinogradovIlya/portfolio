-- Упражнение 04: Неповторяющиеся чтения для уровня SERIALIZABLE
-- Демонстрация как SERIALIZABLE предотвращает аномалию Non-Repeatable Reads

-- ========== СЕССИЯ #1 ==========
-- Шаг 1: Устанавливаем уровень изоляции SERIALIZABLE и начинаем транзакцию
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;

-- Шаг 2: ПЕРВОЕ чтение рейтинга Pizza Hut
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый результат: rating = 3.6 (из предыдущего упражнения)

-- ========== СЕССИЯ #2 ==========
-- Шаг 1: Начинаем отдельную транзакцию (можно использовать обычный уровень)
BEGIN;

-- Шаг 2: Обновляем рейтинг Pizza Hut на 3.0
UPDATE pizzeria
SET rating = 3.0
WHERE name = 'Pizza Hut';

-- Шаг 3: Фиксируем изменения
COMMIT;

-- ========== СЕССИЯ #1 ==========
-- Шаг 3: ВТОРОЕ чтение того же рейтинга Pizza Hut В ТОЙ ЖЕ ТРАНЗАКЦИИ
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- ВАЖНО: Результат будет ТОТ ЖЕ: rating = 3.6 (не изменился!)
-- SERIALIZABLE гарантирует повторяемость чтений

-- Шаг 4: Попытка зафиксировать транзакцию
-- ОЖИДАЕТСЯ ОШИБКА: "could not serialize access due to read/write dependencies among transactions"
COMMIT;