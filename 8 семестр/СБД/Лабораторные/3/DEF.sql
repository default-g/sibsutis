DROP SEQUENCE my_sequence;
DROP TABLE lab3_def1;

CREATE SEQUENCE my_sequence
  INCREMENT BY 1
  START WITH 1
  MAXVALUE 100
  NOCYCLE
  NOCACHE;

create table lab3_def1(
  did NUMBER(6,0) NOT NULL,
  dname VARCHAR2(30) NOT NULL,
  dow VARCHAR2(30) NOT NULL,
  teacher_name VARCHAR2(50) NOT NULL
);

INSERT INTO lab3_def1 VALUES (my_sequence.NEXTVAL, 'Disc.1', 'Monday', 'Agalakov');
INSERT INTO lab3_def1 VALUES (my_sequence.NEXTVAL, 'Disc.2', 'Tuesday', 'Diyachkova');
INSERT INTO lab3_def1 VALUES (my_sequence.NEXTVAL, 'Disc.3', 'Wednesday', 'Pavlova');
INSERT INTO lab3_def1 VALUES (my_sequence.NEXTVAL, 'Disc.4', 'Thursday', 'Machinkina');
INSERT INTO lab3_def1 VALUES (my_sequence.NEXTVAL, 'Disc.5', 'Friday', 'Ruban');

SELECT * FROM lab3_def1;
/
DROP TABLE lab3_def2;
CREATE TABLE lab3_def2 (
  discipline_id NUMBER,
  discipline_name VARCHAR2(100),
  monday VARCHAR2(100),
  tuesday VARCHAR2(100),
  wednesday VARCHAR2(100),
  thursday VARCHAR2(100),
  friday VARCHAR2(100),
  saturday VARCHAR2(100),
  sunday VARCHAR2(100)
);

CREATE OR REPLACE PACKAGE Schedule_Package IS
  PROCEDURE fill_schedule_table;
END Schedule_Package;
/

CREATE OR REPLACE PACKAGE BODY Schedule_Package IS
  PROCEDURE fill_schedule_table AS
  BEGIN
    FOR schedule_record IN (SELECT * FROM lab3_def1) LOOP
      INSERT INTO lab3_def2 (discipline_id, discipline_name,
        monday, tuesday, wednesday, thursday, friday, saturday, sunday)
      VALUES (schedule_record.did, schedule_record.dname,
        CASE WHEN schedule_record.dow = 'Monday' THEN schedule_record.teacher_name ELSE '-' END,
        CASE WHEN schedule_record.dow = 'Tuesday' THEN schedule_record.teacher_name ELSE '-' END,
        CASE WHEN schedule_record.dow = 'Wednesday' THEN schedule_record.teacher_name ELSE '-' END,
        CASE WHEN schedule_record.dow = 'Thursday' THEN schedule_record.teacher_name ELSE '-' END,
        CASE WHEN schedule_record.dow = 'Friday' THEN schedule_record.teacher_name ELSE '-' END,
        CASE WHEN schedule_record.dow = 'Saturday' THEN schedule_record.teacher_name ELSE '-' END,
        CASE WHEN schedule_record.dow = 'Sunday' THEN schedule_record.teacher_name ELSE '-' END);
    END LOOP;
  END fill_schedule_table;
END Schedule_Package;
/

BEGIN
    Schedule_Package.fill_schedule_table;
END;
/

SELECT * FROM lab3_def2;
