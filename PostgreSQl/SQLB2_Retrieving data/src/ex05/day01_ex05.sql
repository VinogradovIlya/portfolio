select *
from person as per
cross join pizzeria as piz
ORDER BY per.id,
         piz.id;