-- tema curs 3
-- ce exceptii apar pe update si delete cu returning into
select * from bagaje;

declare
    v_id_bagaj bagaje.id_bagaj%type;
    v_id_check_in bagaje.id_check_in%type;
    v_greutate bagaje.greutate%type;
    
begin
    delete from bagaje
    where id_bagaj in (4, 5)
    returning id_bagaj, id_check_in, greutate 
    into v_id_bagaj, v_id_check_in, v_greutate;
    dbms_output.put_line('S-a sters id bagaj ' || v_id_bagaj || ', id check-in ' || v_id_check_in || ', greutate ' || v_greutate);
    exception when no_data_found then dbms_output.put_line('Exceptie no data found');
              when too_many_rows then dbms_output.put_line('Exceptie too many rows');
end;
/


declare
    v_greutate bagaje.greutate%type;
begin
    update bagaje
    set greutate = 20
    where id_bagaj in (4, 5)
    returning greutate 
    into v_greutate;
    dbms_output.put_line('Noua greutate este ' || v_greutate);
    exception when no_data_found then dbms_output.put_line('Exceptie no data found');
              when too_many_rows then dbms_output.put_line('Exceptie too many rows');
end;
/


rollback;

--    if sql%rowcount = 0 then dbms_output.put_line('Nu s-a ?ters nicio linie');
--    else dbms_output.put_line('S-a sters id bagaj ' || v_id_bagaj || ', id check-in ' || v_id_check_in || ', greutate ' || v_greutate);
--    end if;


--------------------------------------------------------------------------------------------------------------------------------


-- tema curs 4
-- exemple de utilizare cu stocare de diacritice si caractere speciale ce au nevoie de mai mult de un byte
-- char, varchar2, nchar, nvarchar2

declare
    c1 char(2) := '@';
    c2 char(4) := '@@';
    c3 nchar(1) := '@';
    c4 nchar(2) := '@@';
    v1 varchar2(2) := '@';
    v2 varchar2(4) := '@@';
    v3 nvarchar2(1) := '@';
    v4 nvarchar2(2) := '@@';
begin
    dbms_output.put_line('c1 = ' || c1);
    dbms_output.put_line('c2 = ' || c2);
    dbms_output.put_line('c3 = ' || c3);
    dbms_output.put_line('c4 = ' || c4);
    dbms_output.put_line('v1 = ' || v1);
    dbms_output.put_line('v2 = ' || v2);
    dbms_output.put_line('v3 = ' || v3);
    dbms_output.put_line('v4 = ' || v4);
end;
/


--------------------------------------------------------------------------------------------------------------------------------


-- tema curs 4.3
-- laborator plsql2 e2/e3
-- cea pe care o facem cu tablou imbricat sa o facem cu multiset in sql
drop table excursie;
drop type tip_orase;

create or replace type tip_orase is table of varchar2(20);
/ 

create table excursie (
    cod_excursie number(4),
    denumire varchar2(20),
    orase tip_orase,
    status varchar2(20))
    nested table orase store as tabel_orase
/

-- a
begin
    insert into excursie
    values (1, 'Norvegia', tip_orase('Oslo', 'Bergen', 'Trondheim', 'Tromso'), 'disponibila');
    insert into excursie
    values (2, 'Munte', tip_orase('Sinaia', 'Brasov', 'Predeal'), 'disponibila');
    insert into excursie
    values (3, 'Grecia', tip_orase('Salonic', 'Atena'), 'anulata');
    insert into excursie
    values (4, 'Danemarca', tip_orase('Copenhaga', 'Aalborg'), 'disponibila');
    insert into excursie
    values (5, 'Austria', tip_orase('Viena', 'Salzburg', 'Innsbruck'), 'anulata');
end;
/

select * from excursie;

-- b
-- Actualiza?i coloana orase pentru o excursie specificat?

-- ad?uga?i un ora? nou în list?, ce va fi ultimul vizitat în excursia respectiv?
declare
    v_cod excursie.cod_excursie%type := 5;
    v_oras varchar2(20) := 'Linz';
begin
    update excursie
    set orase = orase multiset union all tip_orase(v_oras)
    where cod_excursie = v_cod;
end;
/

select * from excursie;
rollback;

-- ad?uga?i un ora? nou în list?, ce va fi al doilea ora? vizitat în excursia respectiv?
declare
    v_cod excursie.cod_excursie%type := 5;
    v_oras varchar2(20) := 'Graz';
    v_orase tip_orase;
begin
    select orase
    into v_orase
    from excursie
    where cod_excursie = v_cod;

    update excursie
    set orase = (tip_orase(v_orase(1)) multiset union all tip_orase(v_oras)) multiset union all (v_orase multiset except tip_orase(v_orase(1)))
    where cod_excursie = v_cod;
end;
/

commit;
select * from excursie;
rollback;

-- inversa?i ordinea de vizitare a dou? dintre ora?e al c?ror nume este specificat
declare
    v_cod excursie.cod_excursie%type := 5;
    v_orase tip_orase;
    oras1 varchar2(20) := 'Salzburg';
    oras2 varchar2(20) := 'Innsbruck';
begin
    select orase
    into v_orase
    from excursie
    where cod_excursie = v_cod;
    
    for i in 1..cardinality(v_orase) loop
        if v_orase(i) = oras1 then
            v_orase(i) := oras2;
        elsif v_orase(i) = oras2 then
            v_orase(i) := oras1;
        end if;
    end loop;
    
    update excursie
    set orase = v_orase
    where cod_excursie = v_cod;
end;
/

commit;
select * from excursie;
rollback;            

-- elimina?i din list? un ora? al c?rui nume este specificat
declare
    v_cod excursie.cod_excursie%type := 5;
    v_oras varchar2(20) := 'Graz';
begin
    update excursie
    set orase = orase multiset except tip_orase(v_oras)
    where cod_excursie = v_cod;
end;
/

select * from excursie;
rollback;

-- c
-- Pentru o excursie al c?rui cod este dat, afi?a?i num?rul de ora?e vizitate, respectiv numele ora?elor
declare
    v_cod excursie.cod_excursie%type := 5;
    v_orase tip_orase;
begin
    select orase
    into v_orase
    from excursie
    where cod_excursie = v_cod;
    
    dbms_output.put_line('Excursia viziteaza ' || cardinality(v_orase) || ' orase: ');
    for i in 1..cardinality(v_orase) loop
        dbms_output.put_line(v_orase(i));
    end loop;
end;
/

select * from excursie;
rollback;

-- d
-- Pentru fiecare excursie afi?a?i lista ora?elor vizitate
declare
    type tip_coduri is table of excursie.cod_excursie%type;
    v_coduri tip_coduri;
    v_orase tip_orase;
    v_nume excursie.denumire%type;
begin
    select cod_excursie 
    bulk collect into v_coduri
    from excursie;
    
    for i in 1..cardinality(v_coduri) loop
        select denumire 
        into v_nume
        from excursie
        where cod_excursie = v_coduri(i);
        
        dbms_output.put_line('Excursia ' || v_nume || ': ');
        
        select orase 
        into v_orase
        from excursie
        where cod_excursie = v_coduri(i);
        
        for i in 1..cardinality(v_orase) loop
            dbms_output.put_line(v_orase(i));
        end loop;
        dbms_output.new_line;
    end loop;
end;
/

select * from excursie;
rollback;

-- e
-- Anula?i excursiile cu cele mai pu?ine ora?e vizitate
declare
    type tip_coduri is table of excursie.cod_excursie%type;
    v_coduri tip_coduri;
    v_orase tip_orase;
    v_nume excursie.denumire%type;
    v_nr_min number(4) := 1000;
begin
    select cod_excursie 
    bulk collect into v_coduri
    from excursie;
    
    for i in 1..cardinality(v_coduri) loop
        select orase 
        into v_orase
        from excursie
        where cod_excursie = v_coduri(i);
        
        if cardinality(v_orase) < v_nr_min then
            v_nr_min := cardinality(v_orase);
        end if;
    end loop;
    
    for i in 1..cardinality(v_coduri) loop
        select orase 
        into v_orase
        from excursie
        where cod_excursie = v_coduri(i);
        
        if cardinality(v_orase) = v_nr_min then
            update excursie
            set status = 'anulata'
            where cod_excursie = v_coduri(i);
        end if;
    end loop;
end;
/

select * from excursie;
rollback;


--------------------------------------------------------------------------------------------------------------------------------


-- tema curs 5
-- 5.2.1 exemplul 5.6
-- argumente pro si contra - mai bine cu cursor si bulk collect into colectie sau direct select bulk collect into colectie

create table exemple (
    id number(6),
    nume varchar2(30)
);

begin
    for i in 1..100000 loop
        insert into exemple
        values (i, 'nume');
    end loop;
end;
/

select * from exemple;

-- cursor si bulk collect into colectie
declare
    type tab_imb is table of exemple%rowtype;
    v_exemple tab_imb;
    cursor c is select * from exemple;
begin
    open c;
    fetch c bulk collect into v_exemple;
    close c;
end;
/

-- direct select bulk collect into colectie
declare
    type tab_imb is table of exemple%rowtype;
    v_exemple tab_imb;
begin
    select *
    bulk collect into v_exemple
    from exemple;
end;
/


    