select distinct p.name
from person p
join person_order po ON po.person_id = p.id
join menu m ON m.id = po.menu_id
where p.gender = 'female'
    and m.pizza_name in ('cheese pizza',
                         'pepperoni pizza')
group by p.id, p.name
having count(distinct m.pizza_name) = 2
order by p.name ;