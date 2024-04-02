DECLARE
  v_missing_code NUMBER;
  ord_max NUMBER;
  ord_min NUMBER;
  ord_avg NUMBER;
  rating_less_than_avg EXCEPTION;
  cust_name varchar2(100);
  cnum_of_cust NUMBER;

BEGIN
  SELECT MIN(onum) INTO ord_min FROM ord;
  SELECT MAX(onum) INTO ord_max FROM ord;
  SELECT AVG(amt) INTO ord_avg FROM ord;

  FOR i IN ord_min..ord_max LOOP
    BEGIN
      SELECT cnum INTO cnum_of_cust FROM ord WHERE ord_avg > amt AND onum = i;
      IF cnum_of_cust IS NOT NULL THEN
        RAISE rating_less_than_avg;
      END IF;

    EXCEPTION
      WHEN NO_DATA_FOUND THEN
        NULL;
    END;
  END LOOP;

EXCEPTION
    WHEN rating_less_than_avg THEN
        SELECT cname INTO cust_name FROM cust WHERE cnum = cnum_of_cust;
        DBMS_OUTPUT.PUT_LINE('Rating is less than average for customer ' || cust_name);
END;
/
