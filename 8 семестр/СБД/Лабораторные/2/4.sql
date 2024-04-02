CREATE SEQUENCE mysequence
INCREMENT BY 3
START WITH 3;

CREATE TABLE mytable(id INT, name VARCHAR(255));

INSERT INTO mytable(id, name) VALUES(mysequence.NEXTVAL, 'Biba');
INSERT INTO mytable(id, name) VALUES(mysequence.NEXTVAL, 'Boba');
INSERT INTO mytable(id, name) VALUES(mysequence.NEXTVAL, 'Aboba');

SELECT * FROM mytable;

DROP TABLE mytable;
DROP SEQUENCE mysequence;
