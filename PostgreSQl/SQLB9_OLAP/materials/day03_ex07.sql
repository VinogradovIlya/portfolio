insert into menu values (19, 2, 'greek pizza', 800);

select * from menu
join pizzeria ON pizzeria.id = menu.pizzeria_id
where menu.pizzeria_id = 2;