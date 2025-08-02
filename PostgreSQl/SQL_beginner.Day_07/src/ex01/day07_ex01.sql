select person.name,
       count(*) as count_of_visits
from person_visits
join person ON person.id = person_visits.person_id
group by person.name
order by count_of_visits desc,
         person.name
limit 4;