-- 3
BEGIN 
    DBMS_OUTPUT.PUT_LINE('Invat PL/SQL'); 
END; 
/

-- 6
DECLARE 
    v_dep departments.department_name%TYPE; 
    nr_ang number;
BEGIN 
    SELECT department_name, COUNT(*) INTO v_dep, nr_ang
    FROM employees e, departments d 
    WHERE e.department_id = d.department_id 
    GROUP BY department_name 
    HAVING COUNT(*) = (SELECT MAX(COUNT(*)) 
                        FROM employees 
                        GROUP BY department_id); 
    DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep); 
    DBMS_OUTPUT.PUT_LINE('Numar angajati: '|| nr_ang); 
END; 
/

-- e2
-- a
with days as
    (select to_date('01.10.2023', 'dd.mm.yyyy') + level - 1 day_date
    from dual
    connect by level <= to_char(last_day(to_date('01.10.2023', 'dd.mm.yyyy')), 'dd'))
select to_char(d.day_date, 'dd.mm.yyyy'), (select count(*)
                                            from rental r
                                            where to_char(r.book_date, 'dd.mm.yyyy') like to_char(d.day_date, 'dd.mm.yyyy')) cnt
from days d;

-- b
create table octombrie_aho (
id number(5),
data date);

declare
    cnt number(3) := 0;
    data_aux date := '01-oct-2023';

begin
    loop
        insert into octombrie_aho
        values (cnt, data_aux + cnt);
        
        cnt := cnt + 1;
        exit when cnt = 31;
    end loop;
end;
/

select * from octombrie_aho;


-- e3
-- Defini?i un bloc anonim în care s? se determine num?rul de filme (titluri) împrumutate de un membru al c?rui nume
-- este introdus de la tastatur?. Trata?i urm?toarele dou? situa?ii: nu exist? nici un membru cu nume dat; 
-- exist? mai mul?i membrii cu acela?i nume.

declare
    v_nume member.last_name%type := '&v_nume';
    v_id_membru member.member_id%type;
    v_nr_filme number(3);
    
begin
    select member_id
    into v_id_membru
    from member
    where lower(last_name) like lower(v_nume);
    
    begin
        select count(distinct title_id)
        into v_nr_filme
        from rental
        where member_id = v_id_membru;
        dbms_output.put_line('Nr filme imprumutate = ' || v_nr_filme);
    end;
    
exception when no_data_found then dbms_output.put_line('Nu exista niciun membru cu acest nume');
          when too_many_rows then dbms_output.put_line('Exista mai multi membri cu acest nume');
end;
/


-- e4
-- Modifica?i problema anterioar? astfel încât s? afi?a?i ?i urm?torul text:
-- Categoria 1 (a împrumutat mai mult de 75% din titlurile existente)
-- Categoria 2 (a împrumutat mai mult de 50% din titlurile existente)
-- Categoria 3 (a împrumutat mai mult de 25% din titlurile existente)
-- Categoria 4 (altfel)

declare
    v_nume member.last_name%type := '&v_nume';
    v_id_membru member.member_id%type;
    v_nr_filme number(3);
    v_nr_total_filme number(3);
    
begin
    select member_id
    into v_id_membru
    from member
    where lower(last_name) like lower(v_nume);
    
    begin
        select count(*)
        into v_nr_total_filme
        from title;
    end;
    
    begin
        select count(distinct title_id)
        into v_nr_filme
        from rental
        where member_id = v_id_membru;
        dbms_output.put_line('Nr filme imprumutate = ' || v_nr_filme);
        
        case when v_nr_filme > 75/100 * v_nr_total_filme
                  then dbms_output.put_line('Categoria 1');
             when v_nr_filme > 50/100 * v_nr_total_filme
                  then dbms_output.put_line('Categoria 2');
             when v_nr_filme > 25/100 * v_nr_total_filme
                  then dbms_output.put_line('Categoria 3');
             else dbms_output.put_line('Categoria 4');
        end case;
    end;
    
exception when no_data_found then dbms_output.put_line('Nu exista niciun membru cu acest nume');
          when too_many_rows then dbms_output.put_line('Exista mai multi membri cu acest nume');
end;
/


-- e5
-- Crea?i tabelul member_*** (o copie a tabelului member). Ad?uga?i în acest tabel coloana discount, care va reprezenta 
-- procentul de reducere aplicat pentru membrii, în func?ie de categoria din care fac parte ace?tia:
-- 10% pentru membrii din Categoria 1
-- 5% pentru membrii din Categoria 2
-- 3% pentru membrii din Categoria 3
-- nimic
-- Actualiza?i coloana discount pentru un membru al c?rui cod este dat de la tastatur?. Afi?a?i un mesaj din care s?
-- reias? dac? actualizarea s-a produs sau nu.

create table member_aho
as select * from member;

alter table member_aho
add discount number(3);


declare
    v_id_membru member_aho.member_id%type := &v_id_membru;
    v_nr_filme number(3);
    v_nr_total_filme number(3);
    v_discount member_aho.discount%type;
    
begin
    select 1
    into v_nr_filme
    from member_aho
    where member_id = v_id_membru;
    
    begin

        select count(*)
        into v_nr_total_filme
        from title;

        select count(distinct title_id)
        into v_nr_filme
        from rental
        where member_id = v_id_membru;
        dbms_output.put_line('Nr filme imprumutate = ' || v_nr_filme);
            
        case when v_nr_filme > 25/100 * v_nr_total_filme
                    then case when v_nr_filme > 75/100 * v_nr_total_filme
                                    then v_discount := 10;
                                when v_nr_filme > 50/100 * v_nr_total_filme
                                    then v_discount := 5;
                                when v_nr_filme > 25/100 * v_nr_total_filme
                                    then v_discount := 3;
                            end case;
                             
                            update member_aho
                            set discount = v_discount
                            where member_id = v_id_membru;
                             
                            dbms_output.put_line('Actualizare reusita');
                             
                 else dbms_output.put_line('Membrul nu se incadreaza in nicio categorie pt discount');
        end case;
    end;
exception when no_data_found then dbms_output.put_line('Nu exista un membru cu acest id');
end;
/

select * from member_aho;

rollback;



