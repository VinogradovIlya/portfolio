insert into menu values (
(select max(menu.id) + 1
from menu
join pizzeria ON pizzeria.id = menu.pizzeria_id
where menu.pizzeria_id = 2), 2, 'sicilian pizza', 900
);

DELETE FROM menu 
WHERE pizza_name = 'sicilian pizza';

select *
from menu
join pizzeria ON pizzeria.id = menu.pizzeria_id
where menu.pizzeria_id = 2;


insert into menu values (
    (select max(id) + 1 from menu), 
    (select id from pizzeria where name = 'Dominos'), 
    'sicilian pizza', 
    900
);

select m.id, m.pizza_name, m.price, p.name as pizzeria_name
from menu m
join pizzeria p on p.id = m.pizzeria_id
where m.pizza_name = 'sicilian pizza';

select * from menu