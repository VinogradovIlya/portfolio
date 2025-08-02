select piz.name,
       piz.rating
from pizzeria piz
left outer join person_visits pv ON pv.pizzeria_id = piz.id
left outer join person ON person.id = pv.person_id
where pv.pizzeria_id is NULL;