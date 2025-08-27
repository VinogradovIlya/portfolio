DROP FUNCTION IF EXISTS fnc_persons_female();


DROP FUNCTION IF EXISTS fnc_persons_male();


CREATE OR REPLACE FUNCTION fnc_persons(pgender varchar DEFAULT 'female') RETURNS
SETOF person AS $$
        SELECT * FROM person WHERE gender = pgender;
$$ LANGUAGE SQL;


select *
from fnc_persons(pgender := 'male');


select *
from fnc_persons();