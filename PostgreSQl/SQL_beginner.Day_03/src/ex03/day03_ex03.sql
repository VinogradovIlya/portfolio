select piz.name as pizzeria_name
from pizzeria piz
where (
    select count(*)
    from person_visits pv
    join person p on p.id = pv.person_id
    where pv.pizzeria_id = piz.id and p.gender = 'male'
) > (
    select count(*)
    from person_visits pv
    join person p on p.id = pv.person_id
    where pv.pizzeria_id = piz.id and p.gender = 'female'
)
union all
select piz.name as pizzeria_name
from pizzeria piz
where (
    select count(*)
    from person_visits pv
    join person p on p.id = pv.person_id
    where pv.pizzeria_id = piz.id and p.gender = 'female'
) > (
    select count(*)
    from person_visits pv
    join person p on p.id = pv.person_id
    where pv.pizzeria_id = piz.id and p.gender = 'male'
)
order by pizzeria_name