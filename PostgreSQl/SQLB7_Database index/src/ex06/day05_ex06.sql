SELECT m.pizza_name AS pizza_name,
       max(rating) OVER (PARTITION BY rating
                         ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
FROM menu m
INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1,
         2;

-- Use EXPLAIN ANALYZE to diagnose query performance
EXPLAIN ANALYZE
SELECT m.pizza_name AS pizza_name,
       max(rating) OVER (PARTITION BY rating
                         ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
FROM menu m
INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1,
         2;


SET enable_seqscan = off;


DROP INDEX IF EXISTS idx_1;

-- Create an index on 'TableName' for better query performance

CREATE INDEX IF NOT EXISTS idx_1 ON pizzeria(id, rating);

-- EXPLAIN ANALYZE
-- SELECT m.pizza_name AS pizza_name,
--        max(rating) OVER (PARTITION BY rating
--                          ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
-- FROM menu m
-- INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
-- ORDER BY 1,
--          2;

DROP INDEX IF EXISTS idx_1;


CREATE INDEX IF NOT EXISTS idx_1 ON pizzeria(rating);

EXPLAIN ANALYZE
SELECT m.pizza_name AS pizza_name,
       max(rating) OVER (PARTITION BY rating
                         ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
FROM menu m
INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1,
         2;


SET enable_seqscan = on;