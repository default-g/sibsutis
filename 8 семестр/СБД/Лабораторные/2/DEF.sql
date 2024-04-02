DECLARE
    CURSOR cust_cursor(city_to_find VARCHAR2) IS SELECT cname, city FROM cust WHERE city = city_to_find;
    cust_name varchar2(20);
    cust_city varchar2(20);
BEGIN
    OPEN cust_cursor('London');

    LOOP
        FETCH cust_cursor INTO cust_name, cust_city;
        EXIT WHEN cust_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Cust: ' || cust_name || ' - ' || 'City ' || cust_city);
    END LOOP;

    CLOSE cust_cursor;
END;
/

DECLARE
    CURSOR salers_cursor IS SELECT sname, comm FROM sal WHERE comm < (SELECT AVG(comm) FROM sal) LIMIT 4;
    sale_name varchar2(20);
    sale_comm varchar2(20);
BEGIN

    FOR saler IN salers_cursor LOOP
        DBMS_OUTPUT.PUT_LINE('Saler: ' || saler.sname || ' - ' || 'Commission ' || saler.comm);
    END LOOP;

    OPEN salers_cursor;
    LOOP
        FETCH salers_cursor INTO sale_name, sale_comm;
       -- EXIT WHEN salers_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Saler: ' || sale_name || ' - ' || 'Commission ' || sale_comm);
    END LOOP;


END;
/
