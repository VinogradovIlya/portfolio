select m.pizza_name,
       m.price,
       piz.name as pizzeria_name,
       pv.visit_date
from person p
join person_visits pv ON pv.person_id = p.id
join pizzeria piz ON piz.id = pv.pizzeria_id
join menu m ON m.pizzeria_id = piz.id
where p.id = 3
    and m.price between 800 and 1000
ORDER BY m.pizza_name,
         m.price,
         piz.name;