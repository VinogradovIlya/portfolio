select distinct piz.name
from person p
join person_visits pv ON pv.person_id = p.id
join pizzeria piz ON piz.id = pv.pizzeria_id
join menu m ON m.pizzeria_id = piz.id
where p.name = 'Dmitriy'
    and pv.visit_date = '2022-01-08'
    and m.price < 800;