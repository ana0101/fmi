-- 4
select category, count(distinct title), count(*), count(r.copy_id)
from rental r, title t
where r.title_id = t.title_id
group by category
having count(*) = (select max(count(*))
                    from rental r, title t
                    where r.title_id = t.title_id
                    group by category);

-- 5
select t.title_id, t.title, count(tc.copy_id)
from title_copy tc, title t
where t.title_id = tc.title_id
and tc.status = 'AVAILABLE'
group by (t.title_id, t.title)
order by t.title_id;

-- 6
select a.title_id, title, copy_id, status status_setat, 
    case when(a.title_id, copy_id) not in (select title_id, copy_id
                                            from rental
                                            where act_ret_date is null)
            then 'AVAILABLE'
            else 'RENTED'
            end status_corect
from title_copy a, title b
where a.title_id = b.title_id;

-- 7 a
select count(*)
from (select a.title_id, title, copy_id, status status_setat,
        case when(a.title_id, copy_id) not in (select title_id, copy_id
                                            from rental
                                            where act_ret_date is null)
            then 'AVAILABLE'
            else 'RENTED'
            end status_corect
        from title_copy a, title b
        where a.title_id = b.title_id)
where status_setat <> status_corect;

-- 7 b aho
create table title_copy_aho
as select * from title_copy;

update title_copy_aho tc
set status = case when(tc.title_id, copy_id) not in (select title_id, copy_id
                                            from rental
                                            where act_ret_date is null)
            then 'AVAILABLE'
            else 'RENTED'
            end
where status <> case when(tc.title_id, copy_id) not in (select title_id, copy_id
                                            from rental
                                            where act_ret_date is null)
                then 'AVAILABLE'
                else 'RENTED'
                end;

select * from title_copy_aho;

-- 8
select (case when exists (select 1
                            from reservation rs, rental rn
                            where rs.title_id = rn.title_id
                            and rs.member_id = rn.member_id
                            and rs.res_date <> rn.book_date)
                        then 'Nu' else 'Da' end)
from dual;

-- 9
select m.member_id, m.last_name, m.first_name, t.title_id, count(r.title_id)
from member m, rental r, title t
where m.member_id(+) = r.member_id
and r.title_id(+) = t.title_id
group by m.member_id, m.first_name, m.last_name, t.title_id, t.title;

-- 10
select m.member_id, m.last_name, m.first_name, t.title_id, tc.copy_id, count(tc.copy_id)
from member m, rental r, title t, title_copy tc
where m.member_id(+) = r.member_id
and t.title_id = r.title_id(+)
and t.title_id = tc.title_id
group by m.member_id, m.first_name, m.last_name, t.title_id, t.title, tc.copy_id;

-- 11
select t.title_id, tc.copy_id, tc.status, count(tc.copy_id)
from title t, title_copy tc, rental r
where t.title_id = tc.title_id
and tc.title_id = r.title_id
and tc.copy_id = r.copy_id
group by t.title_id, tc.copy_id, tc.status
having count(tc.copy_id) = (select max(count(tc2.copy_id))
                            from title t2, title_copy tc2, rental r2
                            where t2.title_id = t.title_id
                            and t2.title_id = tc2.title_id
                            and tc2.title_id = r2.title_id
                            and tc2.copy_id = r2.copy_id
                            group by t2.title_id, tc2.copy_id)
order by 1, 2;

-- 12 a
declare 
    zi int;
    nr int;
begin
    dbms_output.enable; 
    for zi in 1..2 loop
        begin
            select count(*) into nr
            from rental
            where zi = extract(day from book_date)
            and extract(month from book_date) = extract(month from sysdate)
            group by zi;
            dbms_output.put_line('Ziua ' || zi || ' imprumuturi ' || nr);
        exception when no_data_found
        then dbms_output.put_line('Ziua ' || zi || ' imprumuturi ' || 0);
        end;
    end loop;
end;
/

-- 12 b
select extract(day from book_date) as zi, count(*) as nr_imprumuturi
from rental
where extract(month from book_date) = extract(month from sysdate)
group by extract(day from book_date)
order by 1;

-- 12 c
declare 
    zi int;
    nr int;
begin
    dbms_output.enable; 
    for zi in 1..31 loop
        begin
            select count(*) into nr
            from rental
            where zi = extract(day from book_date)
            and extract(month from book_date) = extract(month from sysdate)
            group by zi;
            dbms_output.put_line('Ziua ' || zi || ' imprumuturi ' || nr);
        exception when no_data_found
        then dbms_output.put_line('Ziua ' || zi || ' imprumuturi ' || 0);
        end;
    end loop;
end;
/


select * from rental
order by book_date;

select sysdate
from dual;





