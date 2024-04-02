DROP TABLE salesmen;
DROP SEQUENCE salesmen_sequence;
DROP SEQUENCE salesmen_sequence2;

CREATE TABLE salesmen(id INT, name VARCHAR(255), min_price FLOAT);
CREATE SEQUENCE salesmen_sequence INCREMENT BY 2 START WITH 5000;
CREATE SEQUENCE salesmen_sequence2 MINVALUE -9999999  MAXVALUE 0 START WITH -1 INCREMENT BY -1;

DECLARE
    CURSOR salesmen_cursor IS
        SELECT sal.snum, sal.sname, MIN(ord.amt) AS min_sum
        FROM sal
        LEFT JOIN ord ON sal.snum = ord.snum
        GROUP BY sal.snum, sal.sname;
BEGIN
    FOR salesman IN salesmen_cursor LOOP
        IF MOD(salesmen_cursor%ROWCOUNT, 2) = 0 THEN
            INSERT INTO salesmen VALUES(salesmen_sequence2.NEXTVAL, salesman.sname, salesman.min_sum);
        ELSE
            INSERT INTO salesmen VALUES(salesmen_sequence.NEXTVAL, salesman.sname, salesman.min_sum);
        END IF;
    END LOOP;
END;
/

SELECT * FROM salesmen;
