SELECT DISTINCT developer FROM operation_systems WHERE type = (SELECT MIN(type) FROM operation_systems);
