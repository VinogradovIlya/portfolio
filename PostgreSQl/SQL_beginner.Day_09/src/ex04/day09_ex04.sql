CREATE OR REPLACE FUNCTION fnc_persons_female() RETURNS
SETOF person AS $$
    SELECT * FROM person WHERE gender = 'female';
$$ LANGUAGE SQL;


CREATE OR REPLACE FUNCTION fnc_persons_male() RETURNS
SETOF person AS $$
    SELECT * FROM person WHERE gender = 'male';
$$ LANGUAGE SQL;


SELECT *
FROM fnc_persons_male();


SELECT *
FROM fnc_persons_female();