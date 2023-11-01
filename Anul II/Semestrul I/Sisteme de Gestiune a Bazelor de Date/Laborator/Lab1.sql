select * from employees;

select extract(day from sysdate), extract(month from sysdate), extract(year from sysdate)
from dual;

select table_name from user_tables;

select 'drop table ' || table_name || ';'
from user_tables;

spool C:\Users\anama\Documents/sterg_tabele.sql
select 'drop table ' || table_name || ';'
from user_tables;
spool off;