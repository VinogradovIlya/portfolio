drop materialized view if exists mv_dmitriy_visits_and_eats;


create materialized view mv_dmitriy_visits_and_eats as
select distinct pizzeria.name
from person
join person_visits ON person_visits.person_id = person.id
join pizzeria ON pizzeria.id = person_visits.pizzeria_id
join menu ON menu.pizzeria_id = pizzeria.id
where person.name = 'Dmitriy'
    and person_visits.visit_date = '2022-01-08'
    and menu.price < 800 ;


select *
from mv_dmitriy_visits_and_eats;