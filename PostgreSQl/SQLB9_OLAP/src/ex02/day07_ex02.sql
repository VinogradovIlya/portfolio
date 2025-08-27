
    (SELECT p.name,
            COUNT(*) as count,
            'order' as action_type
     FROM pizzeria p
     JOIN menu m ON p.id = m.pizzeria_id
     JOIN person_order po ON m.id = po.menu_id
     GROUP BY p.name
     ORDER BY count DESC
     LIMIT 3)
UNION ALL
    (SELECT p.name,
            COUNT(*) as count,
            'visit' as action_type
     FROM pizzeria p
     JOIN person_visits pv ON p.id = pv.pizzeria_id
     GROUP BY p.name
     ORDER BY count DESC
     LIMIT 3)
ORDER BY action_type ASC,
         count DESC;