DECLARE
    CURSOR orders_after(order_date DATE) IS
        SELECT onum, odate FROM ord WHERE order_date < TO_DATE(odate);
BEGIN
    FOR order_after IN orders_after(TO_DATE('01/04/2010')) LOOP
        DBMS_OUTPUT.PUT_LINE('Заказ №' || order_after.onum || ' - ' || order_after.odate );
    END LOOP;
END;
