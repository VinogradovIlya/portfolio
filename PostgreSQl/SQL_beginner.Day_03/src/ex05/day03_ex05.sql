with Andrey_visits as
    (select pizzeria.name as pizzeria_name
     from person
     join person_visits ON person_visits.person_id = person.id
     join pizzeria ON pizzeria.id = person_visits.pizzeria_id
     where person.name = 'Andrey' ),
     Andrey_orders as
    (select pizzeria.name as pizzeria_name
     from person
     join person_order ON person_order.person_id = person.id
     join menu ON menu.id = person_order.menu_id
     join pizzeria ON pizzeria.id = menu.pizzeria_id
     where person.name = 'Andrey' )
select pizzeria_name
from Andrey_visits
except
select pizzeria_name
from Andrey_orders
order by pizzeria_name