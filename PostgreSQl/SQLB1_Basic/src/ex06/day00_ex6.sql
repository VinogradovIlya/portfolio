SELECT
    (SELECT name
     FROM person
     WHERE person.id = person_order.person_id) AS NAME, -- this is an internal query in a main SELECT clause
 CASE
     WHEN
              (SELECT name
               FROM person
               WHERE person.id = person_order.person_id) = 'Denis' THEN 'true'
     ELSE 'false'
 END AS CHECK_NAME
FROM person_order
WHERE (menu_id BETWEEN 13 AND 14
       OR menu_id = 18)
    AND order_date = '2022-01-07';