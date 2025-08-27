-- Упражнение 02: Потерянное обновление для уровня REPEATABLE READ
-- Демонстрация аномалии потерянного обновления под изоляцией REPEATABLE READ

-- ========== СЕССИЯ #1 ==========
-- Шаг 1: Устанавливаем уровень изоляции REPEATABLE READ и начинаем транзакцию
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Шаг 2: Читаем текущий рейтинг Pizza Hut
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый результат: rating = 3.6 (из предыдущего упражнения)

-- ========== СЕССИЯ #2 ==========
-- Шаг 1: Устанавливаем уровень изоляции REPEATABLE READ и начинаем транзакцию
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Шаг 2: Читаем текущий рейтинг Pizza Hut
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый результат: rating = 3.6 (тот же результат)

-- ========== СЕССИЯ #1 ==========
-- Шаг 3: Обновляем рейтинг на 4
UPDATE pizzeria
SET rating = 4
WHERE name = 'Pizza Hut';

-- Проверяем, что обновление прошло в Сессии #1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат в Сессии #1: rating = 4

-- ========== СЕССИЯ #2 ==========
-- Шаг 3: Пытаемся обновить рейтинг на 3.6
-- ВНИМАНИЕ: Эта команда будет заблокирована до COMMIT в Сессии #1
UPDATE pizzeria
SET rating = 3.6
WHERE name = 'Pizza Hut';

-- ========== СЕССИЯ #1 ==========
-- Шаг 4: Фиксируем транзакцию
COMMIT;

-- После COMMIT в Сессии #1, UPDATE в Сессии #2 попытается выполниться
-- Но получит ошибку сериализации!

-- ========== СЕССИЯ #2 ==========
-- Шаг 4: Пытаемся зафиксировать транзакцию
-- ОЖИДАЕТСЯ ОШИБКА: "could not serialize access due to concurrent update"
COMMIT;

-- Итоговая проверка в любой сессии после ошибки:
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Финальный результат: rating = 4 (только изменение из Сессии #1 сохранилось)