drop view if exists v_price_with_discount;


create or replace view v_price_with_discount as
    (select person.name,
            menu.pizza_name,
            menu.price,
            (menu.price - menu.price * 0.1)::integer as discount_price
     from person
     join person_order ON person_order.person_id = person.id
     join menu ON menu.id = person_order.menu_id
     order by person.name,
              menu.pizza_name);


select *
from v_price_with_discount;