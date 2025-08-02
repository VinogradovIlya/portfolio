SELECT person.address,
       pizzeria.name,
       COUNT(person_order.id) AS count_of_orders
FROM person
JOIN person_order ON person_order.person_id = person.id
JOIN menu ON menu.id = person_order.menu_id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY person.address,
         pizzeria.name
ORDER BY person.address,
         pizzeria.name;