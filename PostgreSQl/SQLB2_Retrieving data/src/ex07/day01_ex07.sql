select po.order_date,
       p.name||' (age:'||p.age||')' as person_information
from person_order as po
join person as p on p.id = po.person_id
order by po.order_date,
         person_information;