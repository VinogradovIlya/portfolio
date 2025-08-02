-- Упражнение 03: Аномалия неповторяющихся чтений (Non-Repeatable Reads)
-- Демонстрация под уровнем изоляции READ COMMITTED

-- Проверяем текущий уровень изоляции (должен быть READ COMMITTED)
SHOW TRANSACTION ISOLATION LEVEL;

-- ========== СЕССИЯ #1 ==========
-- Шаг 1: Начинаем транзакцию
BEGIN;

-- Шаг 2: ПЕРВОЕ чтение рейтинга Pizza Hut
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый результат: rating = 4 (из предыдущего упражнения)

-- ========== СЕССИЯ #2 ==========
-- Шаг 1: Начинаем отдельную транзакцию
BEGIN;

-- Шаг 2: Обновляем рейтинг Pizza Hut на 3.6
UPDATE pizzeria
SET rating = 3.6
WHERE name = 'Pizza Hut';

-- Шаг 3: Фиксируем изменения
COMMIT;

-- ========== СЕССИЯ #1 ==========
-- Шаг 3: ВТОРОЕ чтение того же рейтинга Pizza Hut В ТОЙ ЖЕ ТРАНЗАКЦИИ
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый результат: rating = 3.6 (ИЗМЕНИЛОСЬ!)

-- Шаг 4: Фиксируем транзакцию
COMMIT;