SELECT DISTINCT type FROM operation_systems WHERE developer IN (SELECT developer FROM operation_systems WHERE name NOT LIKE '%A%')
