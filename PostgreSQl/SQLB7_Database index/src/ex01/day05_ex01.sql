select m.pizza_name,
       pizzeria.name as pizzeria_name
from pizzeria
join menu m on pizzeria.id = m.pizzeria_id;

set enable_seqscan = off;

-- Use EXPLAIN ANALYZE to diagnose query performance
EXPLAIN ANALYZE
select m.pizza_name,
       pizzeria.name as pizzeria_name
from pizzeria
join menu m on pizzeria.id = m.pizzeria_id;

set enable_seqscan = on;