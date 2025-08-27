select distinct po.order_date as action_date,
                per.name as person_name
from person_order as po
join person as per ON per.id = po.person_id
order by action_date,
         person_name DESC;