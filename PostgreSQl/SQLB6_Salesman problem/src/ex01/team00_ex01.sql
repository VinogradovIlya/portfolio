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
            (previous.tour || ',' || current.point1),
            current.point1,
            current.point2,
            previous.summa + current.cost
        FROM
            nodes AS current
            INNER JOIN tours AS previous ON current.point1 = previous.point2
        WHERE tour NOT LIKE ('%' || current.point1 || '%')
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
),

max_summa AS (
    SELECT MAX(summa) AS max_summa
    FROM complete_tours
)

SELECT
    summa AS total_cost,
    tour
FROM complete_tours
         CROSS JOIN min_summa
         CROSS JOIN max_summa
WHERE summa IN (min_summa, max_summa)
ORDER BY
    total_cost,
    tour;
