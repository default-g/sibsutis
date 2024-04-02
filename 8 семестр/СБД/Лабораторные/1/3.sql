DECLARE
    max_date VARCHAR2(20);
BEGIN
    SELECT MAX(odate) INTO max_date FROM ord;
    DBMS_OUTPUT.PUT_LINE('Max date is: ' || max_date);
END;
