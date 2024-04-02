 select
     count(decode(to_char(odate,'dd.mm.yyyy'),'03.01.2010',onum,null)) "3-e",
     count(decode(to_char(odate,'dd.mm.yyyy'),'04.01.2010',onum,null)) "4-e",
     count(decode(to_char(odate,'dd.mm.yyyy'),'10.01.2010',onum,null)) "10-e"
 from ord;
/

-- DECLARE
--     CURSOR dates IS SELECT DISTINCT odate FROM ord;
--     base_query VARCHAR2(32767);
-- BEGIN
--     base_query := 'SELECT snum, ';
--     FOR ord_date IN dates LOOP
--         base_query := base_query || 'SUM(decode(to_char(odate,''dd.mm.yyyy''),''' || to_char(ord_date.odate, 'dd.mm.yyyy') || ''',amt,0))' || ' AS "' || ord_date.odate || '", ';
--     END LOOP;

--     base_query := RTRIM(base_query, ', ') || ' FROM ord GROUP BY snum ORDER BY snum;';
--     EXECUTE IMMEDIATE base_query;
-- END;
-- /

SELECT
    snum,
    SUM(decode(to_char(odate,'dd.mm.yyyy'),'03.01.2010',amt,0)) "3-e",
    SUM(decode(to_char(odate,'dd.mm.yyyy'),'04.01.2010',amt,0)) "4-e",
    SUM(decode(to_char(odate,'dd.mm.yyyy'),'10.01.2010',amt,0)) "10-e"

FROM ord
GROUP BY snum;
