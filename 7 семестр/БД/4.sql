-- SELECT DISTINCT cust.city FROM cust INNER JOIN sal ON sal.city=cust.city
-- SELECT cust.cnum, cust.cname, sal.sname FROM cust LEFT JOIN sal ON cust.snum=sal.snum
-- SELECT sal.snum, sal.sname, cust.cname FROM sal RIGHT JOIN cust ON sal.snum=cust.snum
-- SELECT cust.cname, ord.onum, ord.amt FROM ord FULL JOIN cust ON ord.cnum=cust.cnum ORDER BY cust.cname
-- SELECT  sal.sname, cust.cname FROM cust CROSS JOIN sal 
