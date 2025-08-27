-- volume в 2 раза больше ?
WITH last_currency_rates AS (
    SELECT DISTINCT
        id,
        name,
        FIRST_VALUE(rate_to_usd) OVER (
            PARTITION BY id 
            ORDER BY updated DESC
        ) as last_rate_to_usd
    FROM currency
),
aggregated_balances AS (
    SELECT 
        b.user_id,
        b.type,
        b.currency_id,
        SUM(b.money) as volume
    FROM balance b
    GROUP BY b.user_id, b.type, b.currency_id
)

SELECT 
    COALESCE(u.name, 'not defined') as name,
    COALESCE(u.lastname, 'not defined') as lastname,
    ab.type,
    ab.volume,
    COALESCE(lcr.name, 'not defined') as currency_name,
    COALESCE(lcr.last_rate_to_usd, 1) as last_rate_to_usd,
    ab.volume * COALESCE(lcr.last_rate_to_usd, 1) as total_volume_in_usd
FROM aggregated_balances ab
LEFT JOIN "user" u ON ab.user_id = u.id
LEFT JOIN last_currency_rates lcr ON ab.currency_id = lcr.id
ORDER BY 
    name DESC, 
    lastname ASC, 
    type ASC;