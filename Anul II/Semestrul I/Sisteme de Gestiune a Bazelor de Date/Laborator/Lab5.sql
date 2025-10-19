-- 5
SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr 
FROM employees sef, employees ang 
WHERE ang.manager_id = sef.employee_id 
GROUP BY sef.employee_id 
ORDER BY nr DESC;

-- E1.
-- Pentru fiecare job (titlu – care va fi afi?at o singur? dat?) ob?ine?i lista angaja?ilor (nume ?i salariu) care lucreaz?
-- în prezent pe jobul respectiv. Trata?i cazul în care nu exist? angaja?i care s? lucreze în prezent pe un anumit job. 
-- Rezolva?i problema folosind:

-- a. cursoare clasice
-- b. ciclu cursoare

-- c. ciclu cursoare cu subcereri
begin
    for v_job in (select job_id, job_title
                    from jobs)
    loop
        dbms_output.put_line('Job-ul ' || v_job.job_title || ': ');
        for v_emp in (select last_name, salary
                        from employees
                        where job_id = v_job.job_id)
        loop
            dbms_output.put_line(v_emp.last_name || ' ' || v_emp.salary);
        dbms_output.new_line;
        end loop;
    end loop;
end;
/

-- d. expresii cursor
declare
    type refcursor is ref cursor;
    cursor c_job is
        select job_title, cursor (select e.last_name, e.salary
                                    from employees e
                                    where e.job_id = j.job_id)
        from jobs j;
    
    v_cursor refcursor;
    v_job_title jobs.job_title%type;
    v_name employees.last_name%type;
    v_salary employees.salary%type;
    
begin
    open c_job;
    loop
        fetch c_job into v_job_title, v_cursor;
        exit when c_job%notfound;
        dbms_output.put_line('Job-ul ' || v_job_title || ': ');
        
        loop
            fetch v_cursor into v_name, v_salary;
            exit when v_cursor%notfound;
            dbms_output.put_line(v_name || ' ' || v_salary);
        end loop;
    end loop;
    close c_job;
end;
/


-- E2.
-- Modifica?i exerci?iul anterior astfel încât s? ob?ine?i ?i urm?toarele informa?ii:
-- un num?r de ordine pentru fiecare angajat care va fi resetat pentru fiecare job
-- pentru fiecare job: num?rul de angaja?i, valoarea lunar? a veniturilor angaja?ilor, valoarea medie a veniturilor angaja?ilor
-- indiferent job: num?rul total de angaja?i, valoarea total? lunar? a veniturilor angaja?ilor, valoarea medie a veniturilor angaja?ilor
declare
    v_nr_ang number(3) := 0;
    v_val_lunara number(30, 2) := 0;
    v_val_medie employees.salary%type := 0;
    v_nr_ang2 number(3) := 0;
    v_val_lunara2 number(30, 2) := 0;
    v_val_medie2 employees.salary%type := 0;
begin
    for v_job in (select job_id, job_title
                    from jobs)
    loop
        dbms_output.put_line('Job-ul ' || v_job.job_title || ': ');
        v_nr_ang := 0;
        v_val_lunara := 0;
        v_val_medie := 0;
        for v_emp in (select last_name, salary
                        from employees
                        where job_id = v_job.job_id)
        loop
            dbms_output.put_line(v_emp.last_name || ' ' || v_emp.salary);
            v_nr_ang := v_nr_ang + 1;
            v_val_lunara := v_val_lunara + v_emp.salary;
            v_nr_ang2 := v_nr_ang2 + 1;
            v_val_lunara2 := v_val_lunara2 + v_emp.salary;
        end loop;
        v_val_medie := v_val_lunara / v_nr_ang;
        dbms_output.put_line('Numar angajati = ' || v_nr_ang);
        dbms_output.put_line('Valoare lunara venituri = ' || v_val_lunara);
        dbms_output.put_line('Valoare medie venituri = ' || v_val_medie);
        dbms_output.new_line;
    end loop;
    v_val_medie2 := v_val_lunara2 / v_nr_ang2;
    dbms_output.put_line('Numar total angajati = ' || v_nr_ang2);
    dbms_output.put_line('Valoare totala lunara venituri = ' || v_val_lunara2);
    dbms_output.put_line('Valoare medie venituri = ' || v_val_medie2);
end;
/


-- E3.
-- Modifica?i exerci?iul anterior astfel încât s? ob?ine?i suma total? alocat? lunar pentru plata salariilor
-- ?i a comisioanelor tuturor angaja?ilor, iar pentru fiecare angajat cât la sut? din aceast? sum? câ?tig? lunar.
declare
    v_suma_totala number(30, 2) := 0;
    v_suma number (10, 2) := 0;
    v_procent number(5, 2);
begin
    for v_venituri in (select employee_id, salary, commission_pct
                        from employees
                        group by employee_id, salary, commission_pct)
    loop
        v_suma_totala := v_suma_totala + v_venituri.salary + v_venituri.salary * nvl(v_venituri.commission_pct, 0);
    end loop;
    dbms_output.put_line('Suma totala = ' || v_suma_totala);
    dbms_output.new_line;

    for v_job in (select job_id, job_title
                    from jobs)
    loop
        dbms_output.put_line('Job-ul ' || v_job.job_title || ': ');
        for v_emp in (select last_name, salary, commission_pct
                        from employees
                        where job_id = v_job.job_id)
        loop
            v_suma := v_emp.salary + v_emp.salary * nvl(v_emp.commission_pct, 0);
            v_procent := v_suma * 100 / v_suma_totala;
            dbms_output.put_line(v_emp.last_name || ': salariu + comision = ' || v_suma || ' = ' || v_procent || '%');
        end loop;
        dbms_output.new_line;
    end loop;
end;
/


-- E4.
-- Modifica?i exerci?iul anterior astfel încât s? ob?ine?i pentru fiecare job primii 5 angaja?i care câ?tig? cel mai mare salariu lunar. 
-- Specifica?i dac? pentru un job sunt mai pu?in de 5 angaja?i.
declare
    v_nr_ang number(3);
begin
    for v_job in (select job_id, job_title
                    from jobs)
    loop
        dbms_output.put_line('Job-ul ' || v_job.job_title || ': ');
        v_nr_ang := 0;
        for v_emp in (select *
                        from (select last_name, salary
                                from employees
                                where job_id = v_job.job_id
                                order by salary desc)
                        where rownum < 6)
        loop
            dbms_output.put_line(v_emp.last_name || ' ' || v_emp.salary);
            v_nr_ang := v_nr_ang + 1;
        end loop;
        if v_nr_ang < 5 then dbms_output.put_line('Sunt mai putin de 5 angajati');
        end if;
        dbms_output.new_line;
    end loop;
end;
/


-- E5.
-- Modifica?i exerci?iul anterior astfel încât s? ob?ine?i pentru fiecare job top 5 angaja?i. 
-- Dac? exist? mai mul?i angaja?i care respect? criteriul de selec?ie care au acela?i salariu, 
-- atunci ace?tia vor ocupa aceea?i pozi?ie în top 5.
declare
    v_nr_ang number(3);
    v_poz number(1);
    v_salariu employees.salary%type;
begin
    for v_job in (select job_id, job_title
                    from jobs)
    loop
        dbms_output.put_line('Job-ul ' || v_job.job_title || ': ');
        v_nr_ang := 0;
        v_poz := 0;
        v_salariu := 0;
        for v_emp in (select last_name, salary
                        from employees
                        where job_id = v_job.job_id
                        order by salary desc)
        loop
            if v_emp.salary <> v_salariu then
                v_poz := v_poz + 1;
                v_salariu := v_emp.salary;
            end if;
            if v_poz < 6 then
                dbms_output.put_line(v_emp.last_name || ' salariu ' || v_emp.salary || ' pozitia ' || v_poz);
            end if;
            v_nr_ang := v_nr_ang + 1;
        exit when v_poz = 6;
        end loop;
        if v_nr_ang < 5 then dbms_output.put_line('Sunt mai putin de 5 angajati');
        end if;
        dbms_output.new_line;
    end loop;
end;
/

