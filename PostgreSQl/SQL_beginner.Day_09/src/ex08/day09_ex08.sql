CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INTEGER DEFAULT 10) 
RETURNS TABLE (fibonacci_number BIGINT) AS $$
DECLARE
    a BIGINT := 0;
    b BIGINT := 1;
    temp BIGINT;
BEGIN
    IF a < pstop THEN
        fibonacci_number := a;
        RETURN NEXT;
    END IF;

    WHILE b < pstop LOOP
        fibonacci_number := b;
        RETURN NEXT;

        temp := a + b;
        a := b;
        b := temp;
    END LOOP;
END;
$$ LANGUAGE plpgsql;


select *
from fnc_fibonacci(100);


select *
from fnc_fibonacci();