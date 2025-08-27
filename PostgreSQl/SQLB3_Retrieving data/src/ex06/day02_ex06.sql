select m.pizza_name,
       piz.name as pizzeria_name
from person_order po
join person p ON p.id = po.person_id
join menu m on m.id = po.menu_id
join pizzeria piz ON piz.id = m.pizzeria_id
where p.name = 'Denis'
    or p.name = 'Anna'
order by m.pizza_name,
         piz.name;