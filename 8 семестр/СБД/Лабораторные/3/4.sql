CREATE OR REPLACE PACKAGE SurnamePack IS
    FUNCTION Longest(surname1 IN VARCHAR2, surname2 IN VARCHAR2, surname3 IN VARCHAR2) RETURN VARCHAR2;
    FUNCTION Shortest(surname1 IN VARCHAR2, surname2 IN VARCHAR2, surname3 IN VARCHAR2) RETURN VARCHAR2;
END SurnamePack;
/

CREATE OR REPLACE PACKAGE BODY SurnamePack IS
    FUNCTION Longest(surname1 IN VARCHAR2, surname2 IN VARCHAR2, surname3 IN VARCHAR2) RETURN VARCHAR2 IS
        max_surname VARCHAR2(100);
        a NUMBER;
        b NUMBER;
        c NUMBER;
    BEGIN
        a := LENGTH(surname1);
        b := LENGTH(surname2);
        c := LENGTH(surname3);

        IF a >= b AND a >= c THEN
            max_surname := surname1;
        ELSIF b >= a AND b >= c THEN
            max_surname := surname2;
        ELSE
            max_surname := surname3;
        END IF;

        RETURN max_surname;
    END;

    FUNCTION Shortest(surname1 IN VARCHAR2, surname2 IN VARCHAR2, surname3 IN VARCHAR2) RETURN VARCHAR2 IS
        min_surname VARCHAR2(100);
        a NUMBER;
        b NUMBER;
        c NUMBER;
    BEGIN
        a := LENGTH(surname1);
        b := LENGTH(surname2);
        c := LENGTH(surname3);

        IF a <= b AND a <= c THEN
            min_surname := surname1;
        ELSIF b <= a AND b <= c THEN
            min_surname := surname2;
        ELSE
            min_surname := surname3;
        END IF;

        RETURN min_surname;
    END;
END SurnamePack;
/

CREATE OR REPLACE PACKAGE SurnameUsingPack IS
    PROCEDURE CallLongest;
    PROCEDURE CallShortest;
END SurnameUsingPack;
/

CREATE OR REPLACE PACKAGE BODY SurnameUsingPack IS
    PROCEDURE CallLongest IS
    BEGIN
        DBMS_OUTPUT.PUT_LINE(SurnamePack.Longest('Обухов', 'Малышев', 'Гулая'));
    END;

    PROCEDURE CallShortest IS
    BEGIN
        DBMS_OUTPUT.PUT_LINE(SurnamePack.Shortest('Обухов', 'Малышев', 'Гулая'));
    END;
END;
/

BEGIN
    SurnameUsingPack.CallShortest();
    SurnameUsingPack.CallLongest();
END;
/
