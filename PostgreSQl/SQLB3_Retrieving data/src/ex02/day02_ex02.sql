-- select coalesce(per.name, '-') as person_name,
--        coalesce(piz.name, '-') as pizzeria_name,
--        pv.visit_date
-- from person_visits pv -- person
-- -- from person
-- full join person per on per.id = pv.person_id
-- full join pizzeria piz on pv.pizzeria_id = piz.id
-- where pv.visit_date between '2022-01-01' and '2022-01-03'
--     -- or pv.visit_date is null
-- order by person_name,
--          pizzeria_name,
--          visit_date;


SELECT coalesce(p.name, '-') AS person_name,
      pv.visit_date, coalesce(pz.name, '-') AS pizzeria_name
FROM person p
FULL JOIN
  (SELECT * FROM person_visits po
  WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') pv ON p.id = pv.person_id
FULL JOIN pizzeria pz ON pz.id = pv.pizzeria_id
ORDER BY 1, 2, 3