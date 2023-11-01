-- 1
DECLARE 
    x NUMBER(1) := 5; 
    y x%TYPE := NULL; 
    
BEGIN 
    IF x <> y THEN DBMS_OUTPUT.PUT_LINE ('valoare <> null este = true'); 
    ELSE DBMS_OUTPUT.PUT_LINE ('valoare <> null este != true'); 
    END IF; 
        
    x := NULL; 
    IF x = y THEN DBMS_OUTPUT.PUT_LINE ('null = null este = true'); 
    ELSE DBMS_OUTPUT.PUT_LINE ('null = null este != true'); 
    END IF; 
END; 
/


-- 4
DECLARE 
    TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER; 
    t tablou_indexat; 
    
BEGIN 
    -- punctul a 
    FOR i IN 1..10 LOOP 
        t(i):=i; 
    END LOOP; 
--    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: '); 
--    
--    FOR i IN t.FIRST..t.LAST LOOP 
--        DBMS_OUTPUT.PUT(t(i) || ' '); 
--    END LOOP; 
--    DBMS_OUTPUT.NEW_LINE;
    
    -- punctul b 
    FOR i IN 1..10 LOOP 
        IF i mod 2 = 1 
            THEN t(i):=null; 
        END IF; 
    END LOOP; 
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
    
    FOR i IN t.FIRST..t.LAST LOOP 
        DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
    END LOOP; 
    DBMS_OUTPUT.NEW_LINE;
    
    -- punctul c 
    t.DELETE(t.first); 
    t.DELETE(5,7); 
    t.DELETE(t.last); 
    DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first || ' si valoarea ' || nvl(t(t.first),0)); 
    DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last || ' si valoarea ' || nvl(t(t.last),0)); 
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: '); 
    FOR i IN t.FIRST..t.LAST LOOP 
        IF t.EXISTS(i) 
            THEN DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' '); 
        END IF; END LOOP; 
    DBMS_OUTPUT.NEW_LINE;
    
    -- punctul d 
    t.delete; 
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/
        

-- e1
declare 
    type tablou_imbricat is table of number;
    t tablou_imbricat := tablou_imbricat();
    v_salariu_vechi employees.salary%type;
    v_salariu_nou employees.salary%type;
    i number(3) := 1;
    
begin
    for v_emp in (select *
                  from (select employee_id
                        from employees
                        where commission_pct is null
                        order by salary)
                  where rownum <= 5)
    loop 
        t.extend;
        t(i) := v_emp.employee_id;
        i := i + 1;
    end loop;
    
    for i in t.first..t.last loop
        update employees
        set salary = salary + 5/100 * salary
        where employee_id = t(i)
        returning salary, salary - + 5/100 * salary
        into v_salaiu_nou, v_salariu_vechi;
        
        dbms_output.put_line('Salariul vechi ' || v_salariu_vechi || ', salariu nou ' || v_salariu_nou);
    end loop;
end;
/


-- e2
create or replace type tip_orase_aho is table of varchar2(20);
/    
    
create table excursie_aho (
    cod_excursie number(4),
    denumire varchar2(20),
    orase tip_orase_aho,
    status varchar2(20))
    nested table orase store as tabel_orase_aho
/

-- a
insert into excursie_aho
values (1, 'Norvegia', tip_orase_aho('Oslo', 'Bergen', 'Trondheim', 'Tromso'), 'disponibila');
insert into excursie_aho
values (2, 'Munte', tip_orase_aho('Sinaia', 'Brasov', 'Predeal'), 'disponibila');
insert into excursie_aho
values (3, 'Grecia', tip_orase_aho('Salonic', 'Atena'), 'anulata');
insert into excursie_aho
values (4, 'Danemarca', tip_orase_aho('Copenhaga', 'Aalborg'), 'disponibila');
insert into excursie_aho
values (5, 'Austria', tip_orase_aho('Viena', 'Salzburg', 'Innsbruck'), 'anulata');

select * from excursie_aho;

-- b
-- Actualiza?i coloana orase pentru o excursie specificat?

-- ad?uga?i un ora? nou în list?, ce va fi ultimul vizitat în excursia respectiv?
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    v_orase.extend;
    v_orase(v_orase.last) := 'Linz';
    
    update excursie_aho
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

-- ad?uga?i un ora? nou în list?, ce va fi al doilea ora? vizitat în excursia respectiv?
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    v_orase.extend;
    for i in reverse 2..v_orase.last-1 loop
        v_orase(i+1) := v_orase(i);
    end loop;
    v_orase(2) := 'Graz';
    
    update excursie_aho
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

-- inversa?i ordinea de vizitare a dou? dintre ora?e al c?ror nume este specificat
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
    oras1 varchar2(20) := 'Salzburg';
    oras2 varchar2(20) := 'Innsbruck';
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    for i in v_orase.first..v_orase.last loop
        if v_orase(i) = oras1 then
            v_orase(i) := oras2;
        elsif v_orase(i) = oras2 then
            v_orase(i) := oras1;
        end if;
    end loop;
    
    update excursie_aho
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

select * from excursie_aho;

-- elimina?i din list? un ora? al c?rui nume este specificat
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
    oras varchar2(20) := 'Graz';
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    for i in v_orase.first..v_orase.last loop
        if v_orase(i) = oras then
            v_orase.delete(i);
        end if;
    end loop;
    
    update excursie_aho
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

select * from excursie_aho;

-- c
-- Pentru o excursie al c?rui cod este dat, afi?a?i num?rul de ora?e vizitate, respectiv numele ora?elor
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    dbms_output.put_line('Excursia viziteaza ' || v_orase.count || ' orase: ');
    for i in v_orase.first..v_orase.last loop
        dbms_output.put_line(v_orase(i));
    end loop;
end;
/

-- d
-- Pentru fiecare excursie afi?a?i lista ora?elor vizitate
declare
    v_orase tip_orase_aho;
    v_nume excursie_aho.denumire%type;
begin
    for e in (select orase, denumire from excursie_aho) loop
        v_orase := e.orase;
        v_nume := e.denumire;
        dbms_output.put_line('Orase excursia ' || v_nume || ': ');
        for i in v_orase.first..v_orase.last loop
            dbms_output.put_line(v_orase(i));
        end loop;
        dbms_output.new_line;
    end loop;
end;
/

-- e
-- Anula?i excursiile cu cele mai pu?ine ora?e vizitate
declare
    v_nr_min number(4) := 1000;
begin
    for e in (select orase from excursie_aho) loop
        if e.orase.count < v_nr_min then 
            v_nr_min := e.orase.count;
        end if;
    end loop;
    
    for e in (select orase, cod_excursie from excursie_aho) loop
        if e.orase.count = v_nr_min then 
            update excursie_aho
            set status = 'anulata'
            where cod_excursie = e.cod_excursie;
        end if;
    end loop;
end;
/

select * from excursie_aho;

rollback;

drop table excursie_aho;
drop type tip_orase_aho;


-- e3
create or replace type tip_orase_aho is varray(10) of varchar2(20);
/   
    
create table excursie_aho (
    cod_excursie number(4),
    denumire varchar2(20),
    orase tip_orase_aho,
    status varchar2(20));

-- a
insert into excursie_aho
values (1, 'Norvegia', tip_orase_aho('Oslo', 'Bergen', 'Trondheim', 'Tromso'), 'disponibila');
insert into excursie_aho
values (2, 'Munte', tip_orase_aho('Sinaia', 'Brasov', 'Predeal'), 'disponibila');
insert into excursie_aho
values (3, 'Grecia', tip_orase_aho('Salonic', 'Atena'), 'anulata');
insert into excursie_aho
values (4, 'Danemarca', tip_orase_aho('Copenhaga', 'Aalborg'), 'disponibila');
insert into excursie_aho
values (5, 'Austria', tip_orase_aho('Viena', 'Salzburg', 'Innsbruck'), 'anulata');

select * from excursie_aho;

-- b
-- Actualiza?i coloana orase pentru o excursie specificat?

-- ad?uga?i un ora? nou în list?, ce va fi ultimul vizitat în excursia respectiv?
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    v_orase.extend;
    v_orase(v_orase.last) := 'Linz';
    
    update excursie_aho
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

select * from excursie_aho;

-- ad?uga?i un ora? nou în list?, ce va fi al doilea ora? vizitat în excursia respectiv?
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    v_orase.extend;
    for i in reverse 2..v_orase.last-1 loop
        v_orase(i+1) := v_orase(i);
    end loop;
    v_orase(2) := 'Graz';
    
    update excursie_aho
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

select * from excursie_aho;

-- inversa?i ordinea de vizitare a dou? dintre ora?e al c?ror nume este specificat
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
    oras1 varchar2(20) := 'Salzburg';
    oras2 varchar2(20) := 'Innsbruck';
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    for i in v_orase.first..v_orase.last loop
        if v_orase(i) = oras1 then
            v_orase(i) := oras2;
        elsif v_orase(i) = oras2 then
            v_orase(i) := oras1;
        end if;
    end loop;
    
    update excursie_aho
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

select * from excursie_aho;

-- elimina?i din list? un ora? al c?rui nume este specificat
declare
    v_orase tip_orase_aho;
    v_orase2 tip_orase_aho := tip_orase_aho();
    v_cod excursie_aho.cod_excursie%type := 5;
    oras varchar2(20) := 'Graz';
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    for i in v_orase.first..v_orase.last loop
        if v_orase(i) <> oras then
            v_orase2.extend;
            v_orase2(v_orase2.last) := v_orase(i);
        end if;
    end loop;
    
    update excursie_aho
    set orase = v_orase2
    where cod_excursie = v_cod;
end;
/

select * from excursie_aho;

-- c
-- Pentru o excursie al c?rui cod este dat, afi?a?i num?rul de ora?e vizitate, respectiv numele ora?elor
declare
    v_orase tip_orase_aho;
    v_cod excursie_aho.cod_excursie%type := 5;
begin
    select orase
    into v_orase
    from excursie_aho
    where cod_excursie = v_cod;
    
    dbms_output.put_line('Excursia viziteaza ' || v_orase.count || ' orase: ');
    for i in v_orase.first..v_orase.last loop
        dbms_output.put_line(v_orase(i));
    end loop;
end;
/

-- d
-- Pentru fiecare excursie afi?a?i lista ora?elor vizitate
declare
    v_orase tip_orase_aho;
    v_nume excursie_aho.denumire%type;
begin
    for e in (select orase, denumire from excursie_aho) loop
        v_orase := e.orase;
        v_nume := e.denumire;
        dbms_output.put_line('Orase excursia ' || v_nume || ': ');
        for i in v_orase.first..v_orase.last loop
            dbms_output.put_line(v_orase(i));
        end loop;
        dbms_output.new_line;
    end loop;
end;
/

-- e
-- Anula?i excursiile cu cele mai pu?ine ora?e vizitate
declare
    v_nr_min number(4) := 1000;
begin
    for e in (select orase from excursie_aho) loop
        if e.orase.count < v_nr_min then 
            v_nr_min := e.orase.count;
        end if;
    end loop;
    
    for e in (select orase, cod_excursie from excursie_aho) loop
        if e.orase.count = v_nr_min then 
            update excursie_aho
            set status = 'anulata'
            where cod_excursie = e.cod_excursie;
        end if;
    end loop;
end;
/

select * from excursie_aho;

rollback;

drop table excursie_aho;
drop type tip_orase_aho;




        
        