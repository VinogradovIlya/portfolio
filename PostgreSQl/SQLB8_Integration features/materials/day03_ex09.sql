-- Смотрим, есть ли уже такие посещения
select p.name, pz.name as pizzeria_name, pv.visit_date
from person_visits pv
join person p on p.id = pv.person_id
join pizzeria pz on pz.id = pv.pizzeria_id
where p.name in ('Denis', 'Irina')
and pz.name = 'Dominos'
and pv.visit_date = '2022-02-24';

insert into person_visits
select
    (select coalesce(max(id), 0)+1
     from person_visits),
    (select id
     from person
     where name = 'Denis'),
    (select id
     from pizzeria
     where name = 'Dominos'), '2022-02-24'
where not exists
        (select 1
         from person_visits pv
         join person p on p.id = pv.person_id
         join pizzeria pz on pz.id = pv.pizzeria_id
         where p.name = 'Denis'
             and pz.name = 'Dominos'
             and pv.visit_date = '2022-02-24' );


insert into person_visits
select
    (select coalesce(max(id), 0)+1
     from person_visits),
    (select id
     from person
     where name = 'Irina'),
    (select id
     from pizzeria
     where name = 'Dominos'), '2022-02-24'
where not exists
        (select 1
         from person_visits pv
         join person p on p.id = pv.person_id
         join pizzeria pz on pz.id = pv.pizzeria_id
         where p.name = 'Irina'
             and pz.name = 'Dominos'
             and pv.visit_date = '2022-02-24' );

select * from person_visits