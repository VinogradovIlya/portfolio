select p.name as person_name,
       m.pizza_name as pizza_name,
       piz.name as pizzeria_name
from person p
join person_order po on po.person_id = p.id
join menu m ON m.id = po.menu_id
join pizzeria piz ON piz.id = m.pizzeria_id
order by person_name,
         pizza_name,
         pizzeria_name;