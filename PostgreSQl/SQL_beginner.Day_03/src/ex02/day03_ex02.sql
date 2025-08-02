select m.pizza_name, m.price, piz.name as pizzeria_name
from menu m 
join pizzeria piz on piz.id = m.pizzeria_id
where not exists (
    select 1
    from person_order po
    where po.menu_id = m.id
)
order by m.pizza_name, m.price;