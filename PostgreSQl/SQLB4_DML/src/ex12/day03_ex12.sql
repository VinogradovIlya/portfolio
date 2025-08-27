-- insert into person_order
-- select
--     (select coalesce(max(id), 0) from person_order) + (select count(*) from person where person.id <= p.id),
--     p.id,
--     (select id from menu where pizza_name = 'greek pizza'),
--     '2022-02-25'
-- from person p;

SELECT count(*) = 9 AS CHECK
FROM person_order
WHERE order_date = '2022-02-25'
    AND menu_id =
        (SELECT id
         FROM menu
         WHERE pizza_name = 'greek pizza');


select *
from person_order;