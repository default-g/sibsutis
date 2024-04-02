DECLARE
    last_name varchar2(20);
BEGIN
    SELECT sname INTO last_name FROM sal WHERE snum = 5000;
EXCEPTION
    when OTHERS then DBMS_OUTPUT.PUT_LINE('No data found');
END;
