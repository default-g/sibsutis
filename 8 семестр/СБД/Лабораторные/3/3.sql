CREATE OR REPLACE PACKAGE Pack_1 IS
    PROCEDURE Sal_cnt(city_param IN VARCHAR2);
    PROCEDURE Cust_cnt(city_param IN VARCHAR2);
END Pack_1;
/

CREATE OR REPLACE PACKAGE BODY Pack_1 IS
    cnt NUMBER(2);

    PROCEDURE Sal_cnt(city_param IN VARCHAR2) IS
        sal_cursor SYS_REFCURSOR; -- Declaration of the cursor
    BEGIN
        OPEN sal_cursor FOR
            SELECT COUNT(*) FROM sal WHERE city = city_param;

        FETCH sal_cursor INTO cnt;
        CLOSE sal_cursor;

        DBMS_OUTPUT.put_line('Sal count for ' || city_param || ' = ' || cnt);

    END Sal_cnt;

    PROCEDURE Cust_cnt(city_param IN VARCHAR2) IS
        cust_cursor SYS_REFCURSOR; -- Declaration of the cursor
    BEGIN
        OPEN cust_cursor FOR
            SELECT COUNT(*) FROM cust WHERE city = city_param;

        FETCH cust_cursor INTO cnt;
        CLOSE cust_cursor;

        DBMS_OUTPUT.put_line('Cust count for ' || city_param || ' = ' || cnt);

    END Cust_cnt;

END Pack_1;
/

BEGIN
    Pack_1.Sal_cnt('London');
    Pack_1.Cust_cnt('London');
END;
/
