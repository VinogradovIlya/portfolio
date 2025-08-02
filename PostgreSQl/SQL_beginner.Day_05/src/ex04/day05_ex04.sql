-- Create an index on 'TableName' for better query performance

CREATE UNIQUE INDEX IF NOT EXISTS idx_menu_unique ON menu(pizzeria_id, pizza_name);

SET enable_seqscan = off;

-- Use EXPLAIN ANALYZE to diagnose query performance
EXPLAIN ANALYZE
SELECT *
FROM menu
WHERE pizzeria_id = 1 AND pizza_name = 'cheese pizza';

SET enable_seqscan = on;