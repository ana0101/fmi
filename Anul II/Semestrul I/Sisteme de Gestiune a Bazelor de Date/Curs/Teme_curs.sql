-- tema curs 3
-- ce exceptii apar p eupdate si delete cu returning into
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


    