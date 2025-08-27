select order_date AS action_date,
       person_id
from person_order INTERSECT
select visit_date AS action_date,
       person_id
from person_visits
ORDER BY action_date, person_id DESC;