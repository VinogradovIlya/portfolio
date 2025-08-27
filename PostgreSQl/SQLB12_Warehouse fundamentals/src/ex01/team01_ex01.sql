WITH balance_with_nearest_rate AS (
    SELECT 
        COALESCE(u.name, 'not defined') as name,
        COALESCE(u.lastname, 'not defined') as lastname,
        c.name as currency_name,
        b.money * c.rate_to_usd as currency_in_usd,
        ROW_NUMBER() OVER (
            PARTITION BY u.name, u.lastname, b.money, b.updated, c.name 
            ORDER BY ABS(EXTRACT(EPOCH FROM (b.updated - c.updated)))
        ) as rn
    FROM balance b
    LEFT JOIN "user" u ON b.user_id = u.id
    INNER JOIN currency c ON b.currency_id = c.id
)

SELECT 
    name,
    lastname, 
    currency_name,
    currency_in_usd
FROM balance_with_nearest_rate
WHERE rn = 1
ORDER BY 
    name DESC, 
    lastname ASC, 
    currency_name ASC;