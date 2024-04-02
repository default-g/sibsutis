create or replace trigger no_romans before update or insert on cust for each row
begin
    if :new.city = 'Rome' then
        raise_application_error(-20001, 'Remember - no Rome');
    end if;
end;
/

INSERT INTO CUST VALUES(1, 'John', 'Rome', 30, 30)
