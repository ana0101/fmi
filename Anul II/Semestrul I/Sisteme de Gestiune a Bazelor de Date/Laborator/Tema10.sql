-- e7
-- S? se creeze un bloc PL/SQL prin care se afi?eaz? num?rul de pasageri care au numarul de rezervari mai mare 
-- decât o valoare dat?. S? se trateze cazul în care niciun pasager nu îndepline?te aceast? condi?ie (excep?ii externe).
declare
    v_rez number := &p_rez;
    v_nr number(6);
    exceptie exception;
begin
    select count(*)
    into v_nr
    from pasageri p
    where (select count(id_rezervare)
           from rezervari
           where id_pasager = p.id_pasager) >= v_rez;
    if (v_nr) = 0 then raise exceptie;
    else dbms_output.put_line('Nr de pasageri este ' || v_nr);
    end if;
exception
    when exceptie then dbms_output.put_line('Nu exista pasageri pentru care sa se indeplineasca aceasta conditie');
    when others then dbms_output.put_line('Alta eroare');
end;
/
