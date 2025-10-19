-- 1
create table emp_aho as
select * from employees;

declare
    v_cod emp_aho.employee_id%type := &v_cod;
    v_salariu emp_aho.employee_id%type;
    v_comision emp_aho.commission_pct%type;
    
begin
    select emp_aho.salary
    into v_salariu
    from emp_aho
    where employee_id = v_cod;
    
    case when v_salariu < 1000 then v_comision := 0.1;
         when v_salariu >= 1000 and v_salariu <= 1500 then v_comision := 0.15;
         when v_salariu > 1500 then v_comision := 0.2;
         when v_salariu is null then v_comision := 0;
    end case;
    
    update emp_aho
    set commission_pct = v_comision
    where employee_id = v_cod;
end;
/
    
select * from emp_aho;   
drop table emp_aho;


-- 2
declare
    v_cod departments.department_id%type;
begin
    select max(department_id)
    into v_cod
    from departments;
    dbms_output.put_line(v_cod);
end;
/


-- 3
declare
    type tab_imb is table of emp_aho%rowtype;
    type emp_tab is table of tab_imb index by pls_integer;
    v_tab emp_tab := emp_tab();
begin
    select *
    into v_tab
    from emp_aho
    where emp_aho.employee_id = 200;
end;
/


-- 5
-- while
declare
    cursor c is select last_name, salary
                from employees
                where department_id = 50;
    v_nume employees.last_name%type;
    v_salariu employees.salary%type;
    
begin
    open c;
    while not c%notfound loop
        fetch c into v_nume, v_salariu;
        dbms_output.put_line(v_nume || ' are salariul ' || v_salariu);
    end loop;
    close c;
end;
/

-- loop
declare
    cursor c is select last_name, salary
                from employees
                where department_id = 50;
    v_nume employees.last_name%type;
    v_salariu employees.salary%type;
    
begin
    open c;
    loop
        fetch c into v_nume, v_salariu;
        exit when c%notfound;
        dbms_output.put_line(v_nume || ' are salariul ' || v_salariu);
    end loop;
    close c;
end;
/

-- for
begin
    for c in (select last_name, salary
              from employees
              where department_id = 50) loop
        dbms_output.put_line(c.last_name || ' are salariul ' || c.salary);
    end loop;
end;
/


