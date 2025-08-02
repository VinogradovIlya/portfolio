drop index if exists idx_person_name;


create index if not exists idx_person_name on person(upper(name));


set enable_seqscan = off;

-- Use EXPLAIN ANALYZE to diagnose query performance
EXPLAIN ANALYZE
select *
from person
WHERE UPPER(name) = 'ANNA';


set enable_seqscan = on;