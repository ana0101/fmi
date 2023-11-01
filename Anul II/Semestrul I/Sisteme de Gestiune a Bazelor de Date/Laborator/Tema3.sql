-- 1(5)
-- Definiti un bloc anonim în care sa se afle numele clasei care are cele mai multe locuri.
-- Rezolvati problema utilizând variabile de legatura. Afisati rezultatul atat din bloc, cat si din exteriorul acestuia. 

variable nume_clasa varchar2(30)
begin
    select c.nume
    into :nume_clasa
    from clase c, locuri l
    where c.id_clasa = l.id_clasa
    group by c.nume
    having count(*) = (select max(count(*))
                        from locuri
                        group by id_clasa);
    dbms_output.put_line('Clasa ' || :nume_clasa);
    exception when too_many_rows then dbms_output.put_line('Exista mai multe clase');
end;
/
print nume_clasa


-- 2(7)
-- Determinati varsta si categoria in care se incadreaza un pasager al carui id este dat de la tastatura. Categoria este determinata astfel:
-- daca varsta este cel mult 17, atunci categoria este 1;
-- daca varsta este cel putin 18 si cel mult 30, atunci categoria este 2;
-- daca varsta este cel putin 31, atunci categoria este 3;
-- Afisati categoria obtinuta.

declare
    v_id pasageri.id_pasager%type := &p_id;
    v_varsta number(3);
    v_categorie number(2);
    
begin
    select trunc((sysdate - data_nastere) / 365)
    into v_varsta
    from pasageri
    where id_pasager = v_id;
    
    if v_varsta < 18
        then v_categorie := 1;
    elsif v_varsta between 18 and 30
        then v_categorie := 2;
    else v_categorie := 3;
    end if;
    
    dbms_output.put_line('Varsta este ' || v_varsta);
    dbms_output.put_line('Categoria este ' || v_categorie);
end;
/


-- 3(9)
-- Scrieti un bloc PL/SQL in care stocati prin variabile de substitutie un id de loc (id_zbor + id_loc), 
-- un id de clasa si procentul cu care se mareste pretul locului. Sa se mute locul în noua clasa si
-- sa i se creasca pretul in mod corespunzator. Daca modificarea s-a putut realiza 
-- (exista in tabelul locuri un loc avand id-ul respectiv) sa se afiseze mesajul “Actualizare realizata”,
-- iar in caz contrar mesajul “Nu exista un loc cu acest id”. Anulati modificarile realizate.

select * from locuri;

define p_id_zbor = 0
define p_id_loc = 4
define p_id_clasa = 1
define p_procent = 30

declare
    v_id_zbor locuri.id_zbor%type := &p_id_zbor;
    v_id_loc locuri.id_loc%type := &p_id_loc;
    v_id_clasa clase.id_clasa%type := &p_id_clasa;
    v_procent number(6) := &p_procent;
    
begin
    update locuri
    set id_clasa = v_id_clasa,
        pret = pret + (v_procent/100 * pret)
    where id_zbor = v_id_zbor
    and id_loc = v_id_loc;
    
    if sql%rowcount = 0
        then dbms_output.put_line('Nu exista un loc cu acest id');
    else dbms_output.put_line('Actualizare realizata');
    end if;
end;
/

rollback;



                        
                        