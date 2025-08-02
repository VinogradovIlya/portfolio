select p.name,
       count(pv.pizzeria_id) as count_of_visits
from person p
join person_visits pv ON pv.person_id = p.id
group by p.name
having count(pv.pizzeria_id) > 3
order by p.name;