WITH visits AS
    (SELECT pizzeria.name,
            COUNT(person_visits.person_id) as visit_count
     FROM person_visits
     JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
     GROUP BY pizzeria.name),
     orders AS
    (SELECT pizzeria.name,
            COUNT(person_order.person_id) as order_count
     FROM person_order
     JOIN menu ON menu.id = person_order.menu_id
     JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
     GROUP BY pizzeria.name)
SELECT COALESCE(v.name, o.name) as name,
       COALESCE(v.visit_count, 0) + COALESCE(o.order_count, 0) as total_count
FROM visits v
FULL OUTER JOIN orders o ON v.name = o.name
ORDER BY total_count DESC,
         name ASC;