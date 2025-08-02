DROP INDEX IF EXISTS idx_person_order_order_date;

-- Create an index on 'TableName' for better query performance

CREATE UNIQUE INDEX IF NOT EXISTS idx_person_order_order_date ON person_order(person_id, menu_id)
WHERE order_date = '2022-01-01';


SET enable_seqscan = off;

-- Use EXPLAIN ANALYZE to diagnose query performance
EXPLAIN ANALYZE
SELECT person_id,
       menu_id,
       order_date
FROM person_order
WHERE person_id = 1
    and menu_id = 1
    AND order_date = '2022-01-01';


SET enable_seqscan = on;