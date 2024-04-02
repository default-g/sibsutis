DECLARE
    CURSOR salers_cursor IS SELECT sname, comm FROM sal WHERE city <> 'London';
    sale_name varchar2(20);
    sale_comm varchar2(20);
BEGIN
   IF NOT salers_cursor%ISOPEN then
    OPEN salers_cursor;
   end if;
   LOOP
    FETCH salers_cursor INTO sale_name, sale_comm;
    DBMS_OUTPUT.PUT_LINE('Saler: ' || sale_name || ' - ' || 'Commission ' || sale_comm);
    IF salers_cursor%ROWCOUNT = 2 OR salers_cursor%NOTFOUND THEN
        EXIT;
    END IF;
   END LOOP;
END;
