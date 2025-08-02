select menu.pizza_name, menu.price, pizzeria.name from menu
join pizzeria ON pizzeria.id = menu.pizzeria_id
order by menu.price ;

INSERT INTO person_visits
SELECT
    (SELECT COALESCE(MAX(id), 0) + 1
     FROM person_visits),
    (SELECT id
     FROM person
     WHERE name = 'Dmitriy'),
    (SELECT DISTINCT pizzeria.id
     FROM menu
     JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
     WHERE price < 800
         AND pizzeria.name NOT IN
             (SELECT name
              FROM mv_dmitriy_visits_and_eats)
         AND pizzeria.id NOT IN
             (SELECT pv.pizzeria_id
              FROM person_visits pv
              JOIN person p ON pv.person_id = p.id
              WHERE p.name = 'Dmitriy'
                  AND pv.visit_date = '2022-01-08' )
     LIMIT 1), '2022-01-08';


SELECT *
FROM mv_dmitriy_visits_and_eats;

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;


SELECT *
FROM mv_dmitriy_visits_and_eats;