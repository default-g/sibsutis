CREATE OR REPLACE TRIGGER dummy AFTER INSERT OR UPDATE OR DELETE ON DEP FOR EACH ROW
DECLARE
    command_used VARCHAR2(10);
BEGIN
    IF INSERTING THEN
        command_used := 'INSERT';
    END IF;

    IF UPDATING THEN
        command_used := 'UPDATE';
    END IF;

    IF DELETING THEN
        command_used := 'DELETE';
    END IF;

    INSERT INTO logs VALUES (command_used, 'DEP', user, sysdate, CURRENT_TIMESTAMP);
END;
/

INSERT INTO DEP VALUES(92);
UPDATE DEP SET id=93 WHERE id=92;
DELETE FROM DEP WHERE id = 93;


SELECT * FROM logs
