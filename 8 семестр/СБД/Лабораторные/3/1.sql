DROP TABLE DEP;

CREATE TABLE DEP(id INT);

INSERT INTO DEP(id) VALUES (1);
INSERT INTO DEP(id) VALUES (2);
INSERT INTO DEP(id) VALUES (3);

CREATE OR REPLACE PROCEDURE change_dep (id_to_change IN INT, new_id IN INT) AS
BEGIN
    UPDATE DEP SET id = new_id WHERE id = id_to_change;
END;
/

BEGIN
    change_dep(1, 4);
END;
/

SELECT * FROM DEP;
