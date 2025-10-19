select * from zboruri;
select * from aeroporturi;
-- Pentru fiecare dintre aeroporturile 1, 2, 3 si 4, obtineti id-ul si numele, precum si lista zborurilor 
-- (id-ul si data de sosire) care sosesc in acel aeroport.
-- Rezolvati problema folosind cele trei tipuri de cursoare studiate.

-- cursor clasic
declare
    cursor c1 is
        select id_aeroport, nume
        from aeroporturi
        where id_aeroport in (1, 2, 3, 4)
        order by 1;
    cursor c2 is
        select id_zbor, data_sosire, id_aeroport_sosire
        from zboruri;
    
    v_id_aeroport aeroporturi.id_aeroport%type;
    v_nume aeroporturi.nume%type;
    v_id_zbor zboruri.id_zbor%type;
    v_data_sosire zboruri.data_sosire%type;
    v_id_aeroport_sosire aeroporturi.id_aeroport%type;
    v_nr number(3);
    
begin
    open c1;
    loop
        fetch c1 into v_id_aeroport, v_nume;
        exit when c1%notfound;
        dbms_output.put_line('Aeroport ' || v_id_aeroport || ' ' || v_nume || ': ');
        v_nr := 0;
        
        open c2;
        loop
            fetch c2 into v_id_zbor, v_data_sosire, v_id_aeroport_sosire;
            exit when c2%notfound;
            if v_id_aeroport = v_id_aeroport_sosire then
                dbms_output.put_line('Zbor ' || v_id_zbor || ' data sosire ' || v_data_sosire);
                v_nr := v_nr + 1;
            end if;
        end loop;
        if v_nr = 0 then dbms_output.put_line('Nu exista zboruri');
        end if;
        dbms_output.new_line;
        close c2;
    end loop;
    close c1;
end;
/


-- ciclu cursor
declare
    cursor c1 is
        select id_aeroport, nume
        from aeroporturi
        where id_aeroport in (1, 2, 3, 4)
        order by 1;
    cursor c2 is
        select id_zbor, data_sosire, id_aeroport_sosire
        from zboruri;
    v_nr number(3);
begin
    for a in c1 loop
        dbms_output.put_line('Aeroport ' || a.id_aeroport || ' ' || a.nume || ': ');
        v_nr := 0;
        for z in c2 loop
            if a.id_aeroport = z.id_aeroport_sosire then
                dbms_output.put_line('Zbor ' || z.id_zbor || ' data sosire ' || z.data_sosire);
                v_nr := v_nr + 1;
            end if;
        end loop;
        if v_nr = 0 then dbms_output.put_line('Nu exista zboruri');
        end if;
        dbms_output.new_line;
    end loop;
end;
/


-- ciclu cursor cu subcereri
declare
    v_nr number(3);
begin
    for v_aero in (select id_aeroport, nume
                    from aeroporturi
                    where id_aeroport in (1, 2, 3, 4)
                    order by 1)
    loop
        dbms_output.put_line('Aeroport ' || v_aero.id_aeroport || ' ' || v_aero.nume || ': ');
        v_nr := 0;
        for v_zbor in (select id_zbor, data_sosire
                        from zboruri
                        where id_aeroport_sosire = v_aero.id_aeroport)
        loop
            dbms_output.put_line('Zbor ' || v_zbor.id_zbor || ' data sosire ' || v_zbor.data_sosire);
            v_nr := v_nr + 1;
        end loop;
        if v_nr = 0 then dbms_output.put_line('Nu exista zboruri');
        end if;
        dbms_output.new_line;
    end loop;
end;
/

        
        