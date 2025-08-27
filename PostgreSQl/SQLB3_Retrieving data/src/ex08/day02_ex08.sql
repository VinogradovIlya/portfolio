select distinct p.name
from person p
join person_order po ON po.person_id = p.id
join menu m ON m.id = po.menu_id
where gender = 'male'
    and (address = 'Moscow'
         or address = 'Samara')
    and (m.pizza_name = 'pepperoni pizza'
         or m.pizza_name = 'mushroom pizza') 
order by p.name desc;