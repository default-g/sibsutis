DECLARE
  v_missing_code NUMBER;
  v_min_cnum NUMBER;
BEGIN
  SELECT MAX(cnum) INTO v_min_cnum FROM cust;

  WHILE v_min_cnum > 0 LOOP
    BEGIN
      SELECT 1 INTO v_missing_code FROM cust WHERE cnum = v_min_cnum;
      v_min_cnum := v_min_cnum - 1;
    EXCEPTION
      WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('No code - ' || v_min_cnum);
        EXIT;
    END;
  END LOOP;
END;
/
