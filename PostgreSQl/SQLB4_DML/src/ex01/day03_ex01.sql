select m.id as menu_id
from menu m 
where not exists (
    select 1
    from person_order po
    where po.menu_id = m.id
)
order by menu_id;