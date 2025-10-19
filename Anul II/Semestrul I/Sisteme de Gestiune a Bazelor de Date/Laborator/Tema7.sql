-- e7
-- 2
-- Defini?i un subprogram prin care s? ob?ine?i cetatenia unui pasager al c?rui nume este specificat. Trata?i toate excep?iile ce pot fi generate.
-- Apela?i subprogramul pentru urm?torii pasageri: Leitz, Petrescu, Smith.
-- Rezolva?i problema folosind o func?ie stocata.

create or replace function f2 (v_nume pasageri.nume%type)
return pasageri.cetatenie%type is 
    v_cetatenie pasageri.cetatenie%type;
    begin
        select cetatenie 
        into v_cetatenie
        from pasageri
        where lower(nume) = lower(v_nume);
        return v_cetatenie;
    exception 
        when no_data_found then raise_application_error(-20000, 'Nu exista pasageri cu numele dat');
        when too_many_rows then raise_application_error(-20001, 'Exista mai multi pasageri cu numele dat');
        when others then raise_application_error(-20002, 'Alta eroare');
end f2;
/

select f2('Leitz') from dual;
select f2('Petrescu') from dual;
select f2('Smith') from dual;


-- 4
-- Rezolva?i exerci?iul folosind o procedur? stocata.
create or replace procedure p4 (v_nume in pasageri.nume%type, v_cetatenie out pasageri.cetatenie%type) is
    begin
        select cetatenie 
        into v_cetatenie
        from pasageri
        where lower(nume) = lower(v_nume);
    exception 
        when no_data_found then raise_application_error(-20000, 'Nu exista pasageri cu numele dat');
        when too_many_rows then raise_application_error(-20001, 'Exista mai multi pasageri cu numele dat');
        when others then raise_application_error(-20002, 'Alta eroare');
end p4;
/

declare
    v_cetatenie pasageri.cetatenie%type;
begin
    p4('Smith', v_cetatenie);
    dbms_output.put_line('Cetatenie ' || v_cetatenie);
end;
/
        


select * from pasageri;