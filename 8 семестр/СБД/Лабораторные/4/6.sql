GRANT CREATE ROLE TO PUBLIC;

-- Определение всех ролей, предоставленных текущему пользователю

-- SELECT * FROM DBA_ROLE_PRIVS WHERE GRANTEE = USER;

-- Определение системных привилегий, назначенных текущей сессии через роли
SELECT * FROM SESSION_PRIVS;

-- Создание роли
CREATE ROLE my_role;

-- Присвоение привилегии на чтение
GRANT SELECT ON dep TO my_role;

-- Присвоение привилегии на изменение
GRANT INSERT, UPDATE, DELETE ON dep TO my_role;
