-- Create an index on 'TableName' for better query performance

CREATE UNIQUE INDEX IF NOT EXISTS idx_person_discounts_unique ON person_discounts (person_id, pizzeria_id);


set enable_seqscan = off;

-- Use EXPLAIN ANALYZE to diagnose query performance
EXPLAIN ANALYZE
SELECT *
FROM person_discounts
WHERE person_id = 1
    AND pizzeria_id = 1;


set enable_seqscan = on;