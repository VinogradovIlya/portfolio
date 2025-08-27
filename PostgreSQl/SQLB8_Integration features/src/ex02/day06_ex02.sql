select person.name,
       menu.pizza_name,
       menu.price,
       (menu.price - menu.price * person_discounts.discount / 100)::INTEGER as discount_price,
       pizzeria.name as pizzeria_name
from person_discounts
join person ON person.id = person_discounts.person_id
join pizzeria ON pizzeria.id = person_discounts.pizzeria_id
join menu ON menu.pizzeria_id = pizzeria.id
order by person.name,
         menu.pizza_name;