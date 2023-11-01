-- 9
-- Definiti tipul insotitori_zbor_2 (vector, dimensiune maxima 5, mentine numere).
-- Creati tabelul zboruri_2 cu urmatoarele campuri: id_zbor number(3),id_avion number(3), 
-- lista insotitori_zbor2. Introduceti 3 linii in tabel. Afisati informatiile din tabel.
-- Stergeti tabelul creat, apoi tipul.

create or replace type insotitori_zbor2 as varray(5) of number(3);
/

create table zboruri2 (
    id_zbor number(3),
    id_avion number(3),
    lista insotitori_zbor2);
    
declare
    v_insotitori insotitori_zbor2 := insotitori_zbor2(1, 3, 5);
    
begin
    insert into zboruri2
    values(0, 1, v_insotitori);
    
    insert into zboruri2
    values(1, 3, null);
    
    insert into zboruri2
    values(2, 2, insotitori_zbor2(2, 4));
end;
/

select * from zboruri2;



rollback;

drop table zboruri2;
drop type insotitori_zbor2;


-- 10
-- Creati tabelul pasageri2 cu coloanele id_pasager si nume din tabelul pasageri.
-- Adaugati in acest tabel un nou camp numit telefon de tip tablou imbricate.
-- Acest tabel va mentine pentru fiecare pasager toate numerele de telefon la care
-- poate fi contactat. Inserati o linie noua in tabel. Actualizati o linie din tabel.
-- Afisati informatiile din tabel. Stergeti tabelul si tipul.

select * from pasageri;

create table pasageri2 as
    select id_pasager, nume
    from pasageri
    where rownum <= 2;
    
create or replace type tip_telefon is table of varchar2(12);
/

alter table pasageri2
add (telefon tip_telefon)
nested table telefon store as tabel_telefon;

insert into pasageri2
values(2, 'Avram', tip_telefon('0712345678', '0723232323'));

update pasageri2
set telefon = tip_telefon('0711111111', '0722222222', '0733333333')
where id_pasager = 1;

select p.id_pasager, t.*
from pasageri2 p, table(p.telefon) t;

select * from pasageri2;


rollback;

drop table pasageri2;
drop type tip_telefon;

    
    