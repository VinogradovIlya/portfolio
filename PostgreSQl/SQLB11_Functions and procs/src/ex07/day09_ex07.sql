CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr NUMERIC[])
RETURNS NUMERIC AS $$
    SELECT MIN(unnest) FROM unnest(arr);
$$ LANGUAGE SQL;

-- CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr NUMERIC[])
-- RETURNS NUMERIC AS $$
-- DECLARE
--     min_val NUMERIC;
--     i NUMERIC;
-- BEGIN
--     min_val := arr[1];
--     FOREACH i IN ARRAY arr LOOP
--         IF i < min_val THEN
--             min_val := i;
--         END IF;
--     END LOOP;
--     RETURN min_val;
-- END;
-- $$ LANGUAGE plpgsql;

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);
