-- e2
-- Defini?i un pachet cu ajutorul c?ruia s? se ob?in? varsta maxima înregistrata pentru pasagerii care
-- au rezervare într-un zbor care ajunge intr-un anumit oras ?i lista pasagerilor care au varsta mai mare sau egala 
-- decât acel maxim. Pachetul va con?ine un cursor ?i un subprogram func?ie.

create or replace package pachet3 as
cursor c_pasageri(nr number) return pasageri%rowtype;
function f_max (v_oras orase.nume%type) return number;
end pachet3;
/

create or replace package body pachet3 as

cursor c_pasageri (nr number) return pasageri%rowtype is
    select *
    from pasageri
    where sysdate - data_nastere >= nr;
    
function f_max (v_oras orase.nume%type) return number is
    maxim number;
begin
    select max(sysdate - data_nastere)
    into maxim
    from pasageri p, rezervari r, zboruri z, aeroporturi a, orase o
    where p.id_pasager = r.id_pasager
    and r.id_zbor = z.id_zbor
    and z.id_aeroport_sosire = a.id_aeroport
    and a.id_oras = o.id_oras
    and lower(o.nume) = lower(v_oras);
    return maxim;
end f_max;
end pachet3;
/

declare
    v_oras orase.nume%type := 'Bucuresti';
    v_maxim number;
    v_lista pasageri%rowtype;
begin
    v_maxim := pachet3.f_max(v_oras);
    for v_lista in pachet3.c_pasageri(v_maxim) loop
        dbms_output.put_line(v_lista.nume || ' ' || (sysdate - v_lista.data_nastere) / 365);
    end loop;
end;
/
