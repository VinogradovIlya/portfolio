CREATE TABLE nodes(
   point1 VARCHAR NOT NULL,
   point2 VARCHAR NOT NULL,
   cost INT NOT NULL
);

INSERT INTO nodes(point1, point2, cost)
VALUES
     ('a', 'b', 10),
     ('c', 'a', 15),
     ('d', 'a', 20),
     ('c', 'b', 35),
     ('d', 'b', 25),
     ('d', 'c', 30);

INSERT INTO nodes(point1, point2, cost)
SELECT point2, point1, cost
FROM nodes;

WITH RECURSIVE tours AS (
    (
        SELECT
            point1 AS tour,
            point1,
            point2,
            cost AS summa
        FROM nodes
        WHERE point1 = 'a'
    )
    UNION ALL
    (
        SELECT
            (previous.tour || ',' || current.point1) AS trace,
            current.point1,
            current.point2,
            previous.summa + current.cost AS summa
        FROM
            nodes AS current
            INNER JOIN tours AS previous ON current.point1 = previous.point2
        WHERE
            tour NOT LIKE ('%' || current.point1 || '%')
    )
),

complete_tours AS (
    SELECT
        summa,
        ('{' || tour || ',' || point2 || '}') AS tour
    FROM tours
    WHERE
        LENGTH(tour) = LENGTH('a,c,d,b')
        AND point2 = 'a'
),

min_summa AS (
    SELECT MIN(summa) AS min_summa
    FROM complete_tours
)

SELECT
    summa AS total_cost,
    tour
FROM complete_tours
         CROSS JOIN min_summa
WHERE summa IN (min_summa)
ORDER BY
    total_cost,
    tour;
