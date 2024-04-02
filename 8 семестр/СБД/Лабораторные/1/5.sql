DECLARE
    RATING_LESS_THAN_200 EXCEPTION;
    user_rating NUMBER;
BEGIN
    SELECT MIN(rating) INTO user_rating FROM cust;

    IF user_rating < 200 THEN
        RAISE RATING_LESS_THAN_200;
    END IF;

EXCEPTION
    WHEN RATING_LESS_THAN_200 THEN
        DBMS_OUTPUT.PUT_LINE('Rating is too small');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Unknown Error');
END;
