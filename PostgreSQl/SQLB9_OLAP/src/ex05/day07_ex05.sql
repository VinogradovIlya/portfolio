select distinct p.name
from person p
join person_order po ON po.person_id = p.id
order by p.name