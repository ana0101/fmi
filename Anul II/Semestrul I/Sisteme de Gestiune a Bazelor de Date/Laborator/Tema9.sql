-- e7
-- a. Crea?i tabelul info_zboruri cu urm?toarele coloane:
-- id_info (codul zborului) – cheie primar?;
-- pret_locuri (suma preturilor tuturor locurilor din zborul respectiv).
-- b. Introduce?i date în tabelul creat anterior corespunz?toare informa?iilor existente în schem?.
-- c. Defini?i un declan?ator care va actualiza automat câmpul pret_locuri atunci când se introduce un nou loc,
-- respectiv se ?terge un loc sau se modific? pretul unui loc.

create table info_zboruri (
    id_info number(4),
    pret_total number(10),
    constraint pk_info_zboruri primary key(id_info)
);

create or replace procedure modific_info (v_id_zbor info_zboruri.id_info%type, v_pret locuri.pret%type) as
begin
    update info_zboruri
    set pret_total = nvl(pret_total, 0) + v_pret
    where id_info = v_id_zbor;
end;
/

create or replace trigger trig4
    after delete or update or insert of pret on locuri
    for each row
begin
    if deleting then
        modific_info(:old.id_zbor, -1 * :old.pret);
    elsif updating then
        modific_info(:old.id_zbor, :new.pret - :old.pret);
    else
        modific_info(:new.id_zbor, :new.pret);
    end if;
end;
/

insert into info_zboruri
values (0, 719);
insert into info_zboruri
values (1, 1020);
insert into info_zboruri
values (2, 1820);
insert into info_zboruri
values (3, 1135);
insert into info_zboruri
values (4, 2475);

select sum(pret)
from locuri
where id_zbor = 4;

select * from info_zboruri;

commit;

-- sterg un loc
delete from locuri
where id_zbor = 4
and id_loc = 19;

-- modific pretul unui loc
update locuri
set pret = pret + 100
where id_zbor = 4
and id_loc = 19;

-- adaug un loc
insert into locuri
values (20, 4, 200, 1);

select *
from locuri
where id_zbor = 4;

rollback;


