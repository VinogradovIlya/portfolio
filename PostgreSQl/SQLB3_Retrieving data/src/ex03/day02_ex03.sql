WITH all_dates AS (
    SELECT generate_series(
        '2022-01-01'::date,
        '2022-01-10'::date,
        '1 day'::interval
    )::date AS visit_date
),
visited_dates AS (
    SELECT DISTINCT visit_date
    FROM person_visits 
    WHERE person_id = 1 OR person_id = 2
)
SELECT ad.visit_date AS missing_date
FROM all_dates ad
LEFT JOIN visited_dates vd ON ad.visit_date = vd.visit_date
WHERE vd.visit_date IS NULL
ORDER BY ad.visit_date;