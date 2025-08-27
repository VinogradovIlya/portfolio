select generated_date as missing_date
from v_generated_dates
except
select visit_date
from person_visits
order by missing_date;