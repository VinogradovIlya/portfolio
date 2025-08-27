select
       p.name
from pizzeria p
where p.id not in
        (select distinct pv.pizzeria_id
         from person_visits pv);


SELECT 
       p.name
FROM pizzeria p
WHERE NOT EXISTS
        (SELECT 1
         FROM person_visits pv
         WHERE pv.pizzeria_id = p.id );