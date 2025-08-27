SELECT *
FROM pizzeria
WHERE rating >= 3.5
    and rating <= 5.0
ORDER BY rating;


SELECT *
FROM pizzeria
WHERE rating BETWEEN 3.5 and 5.0
ORDER BY rating;