select m.pizza_name,
       piz.name as pizzeria_name,
       m.price
from menu m
join pizzeria piz ON m.pizzeria_id = piz.id
where m.pizza_name = 'pepperoni pizza'
    or m.pizza_name = 'mushroom pizza'
order by m.pizza_name, piz.name;