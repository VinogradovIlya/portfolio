select gs.missing_date
from
    (select generate_series('2022-01-01'::date, '2022-01-10'::date, '1 day'::interval)::date as missing_date) gs
left join person_visits pv on gs.missing_date = pv.visit_date
and (pv.person_id = 1
     or pv.person_id = 2)
where pv.visit_date is null
order by gs.missing_date;