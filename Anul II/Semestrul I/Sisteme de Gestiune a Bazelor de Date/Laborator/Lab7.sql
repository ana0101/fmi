CREATE OR REPLACE FUNCTION f2_aho(v_nume employees.last_name%TYPE DEFAULT 'Bell')
RETURN NUMBER IS 
    salariu employees.salary%type; 
    BEGIN 
        SELECT salary 
        INTO salariu 
        FROM employees 
        WHERE last_name = v_nume; 
        RETURN salariu; 
    EXCEPTION WHEN NO_DATA_FOUND THEN RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat'); 
              WHEN TOO_MANY_ROWS THEN RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi angajati cu numele dat'); 
              WHEN OTHERS THEN RAISE_APPLICATION_ERROR(-20002,'Alta eroare!'); 
END f2_aho; 
/

-- 5
VARIABLE ang_man NUMBER 
BEGIN :ang_man:=200; 
END; 
/

CREATE OR REPLACE PROCEDURE p5_aho (nr IN OUT NUMBER) IS 
    BEGIN SELECT manager_id 
    INTO nr 
    FROM employees 
    WHERE employee_id=nr; 
END p5_aho; 
/

EXECUTE p5_aho (:ang_man) 
PRINT ang_man


--6
DECLARE 
    nume employees.last_name%TYPE; 
    PROCEDURE p6 (
        rezultat OUT employees.last_name%TYPE, 
        comision IN employees.commission_pct%TYPE:=NULL, 
        cod IN employees.employee_id%TYPE:=NULL) 
IS 
BEGIN 
    IF (comision IS NOT NULL) THEN 
        SELECT last_name 
        INTO rezultat 
        FROM employees 
        WHERE commission_pct= comision; 
        DBMS_OUTPUT.PUT_LINE('numele salariatului care are comisionul '||comision||' este '||rezultat); 
    ELSE 
        SELECT last_name 
        INTO rezultat 
        FROM employees 
        WHERE employee_id = cod; 
        DBMS_OUTPUT.PUT_LINE('numele salariatului avand codul '|| cod ||' este '||rezultat); 
    END IF; 
END p6; 

BEGIN 
    p6(nume,0.4); 
    p6(nume,cod=>200); 
END; 
/


-- 7
DECLARE 
    medie1 NUMBER(10,2); 
    medie2 NUMBER(10,2); 
    
    FUNCTION medie (v_dept employees.department_id%TYPE) 
        RETURN NUMBER IS 
        rezultat NUMBER(10,2); 
        
    BEGIN 
        SELECT AVG(salary) 
        INTO rezultat 
        FROM employees 
        WHERE department_id = v_dept; 
        RETURN rezultat; 
    END; 
    
    FUNCTION medie (v_dept employees.department_id%TYPE, v_job employees.job_id %TYPE) 
        RETURN NUMBER IS 
        rezultat NUMBER(10,2); 
        
    BEGIN 
        SELECT AVG(salary) 
        INTO rezultat 
        FROM employees 
        WHERE department_id = v_dept 
        AND job_id = v_job; 
        RETURN rezultat; 
    END; 
    
BEGIN 
    medie1:= medie(80); 
    DBMS_OUTPUT.PUT_LINE('Media salariilor din departamentul 80' || ' este ' || medie1); 
    medie2 := medie(80,'SA_MAN'); 
    DBMS_OUTPUT.PUT_LINE('Media salariilor managerilor din' || ' departamentul 80 este ' || medie2); 
END; 
/


-- e1
create table info_aho (
    utilizator varchar2(50),
    data timestamp,
    comanda varchar2(50),
    nr_linii number(5),
    eroare varchar2(200)
);

drop table info_aho;


-- e2
create or replace function f2_aho(v_nume employees.last_name%type default 'Bell')
return number is
    salariu employees.salary%type; 
    begin
        select salary 
        into salariu 
        from employees 
        where last_name = v_nume; 
        
        insert into info_aho
        values (sys.login_user(), systimestamp, 'f2_aho', 1, null);
        
        return salariu; 
        
    exception when no_data_found then 
                insert into info_aho
                values (sys.login_user(), systimestamp, 'f2_aho', 0, 'Nu exista angajati cu numele dat');
                return -1;
              when too_many_rows then 
                insert into info_aho
                values (sys.login_user(), systimestamp, 'f2_aho', 0, 'Exista mai multi angajati cu numele dat');
                return -1;
              when others then
                insert into info_aho
                values (sys.login_user(), systimestamp, 'f2_aho', 0, 'Alta eroare');
                return -1;
end f2_aho; 
/

begin
    dbms_output.put_line('Salariul este ' || f2_aho);
    dbms_output.put_line('Salariul este ' || f2_aho('King'));
    dbms_output.put_line('Salariul este ' || f2_aho('Kimball'));
end;
/

select * from info_aho;


create or replace procedure p4_aho(v_nume in employees.last_name%type) is 
    v_salariu employees.salary%type;
    begin
        select salary
        into v_salariu
        from employees
        where last_name = v_nume;
        
        insert into info_aho
        values (sys.login_user(), systimestamp, 'p4_aho', 1, null);
        
        dbms_output.put_line('Salariul este ' || v_salariu);
    exception 
        when no_data_found then
            insert into info_aho
            values (sys.login_user(), systimestamp, 'p4_aho', 0, 'Nu exista angajati cu numele dat');
            dbms_output.put_line('Nu exista angajati cu numele dat');
        when too_many_rows then
            insert into info_aho
            values (sys.login_user(), systimestamp, 'p4_aho', 0, 'Exista mai multi angajati cu numele dat');
            dbms_output.put_line('Exista mai multi angajati cu numele dat');
        when others then
            insert into info_aho
            values (sys.login_user(), systimestamp, 'p4_aho', 0, 'Alta eroare');
            dbms_output.put_line('Alta eroare');
end p4_aho;
/

begin
    p4_aho('Bell');
    p4_aho('King');
    p4_aho('Kimball');
end;
/

select * from info_aho;



    
    