-- 2
FUNCTION exista(cod_loc dept_***.location_id%TYPE,
manager dept_***.manager_id%TYPE)
RETURN NUMBER IS
rezultat NUMBER:=1;
rez_cod_loc NUMBER;
rez_manager NUMBER;
BEGIN
SELECT count(*) INTO rez_cod_loc
FROM locations
WHERE location_id = cod_loc;
SELECT count(*) INTO rez_manager
FROM emp_***
WHERE employee_id = manager;
IF rez_cod_loc=0 OR rez_manager=0 THEN
rezultat:=0;
END IF;
RETURN rezultat;
END;