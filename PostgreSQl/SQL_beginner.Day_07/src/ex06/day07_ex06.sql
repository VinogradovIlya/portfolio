select piz.name,
       COUNT(po.menu_id) AS count_of_orders,
       ROUND(AVG(m.price), 2) AS average_price,
       MAX(m.price) AS max_price,
       MIN(m.price) AS min_price
from pizzeria piz
join menu m ON m.pizzeria_id = piz.id
join person_order po ON po.menu_id = m.id
group by piz.name
order by piz.name