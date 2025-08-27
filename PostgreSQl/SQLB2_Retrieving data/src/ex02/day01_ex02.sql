SELECT pizza_name
FROM menu -- UNION
INTERSECT
SELECT pizza_name
FROM menu
ORDER BY pizza_name DESC;