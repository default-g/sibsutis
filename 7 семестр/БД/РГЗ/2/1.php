<?php

require 'dbconnection.php';

try {
    $sql = "
    DROP TABLE IF EXISTS sql_commands; CREATE TABLE sql_commands(
        id INTEGER PRIMARY KEY NOT NULL,
        command STRING NOT NULL,
        type STRING NOT NULL
    );

    INSERT INTO sql_commands(command, type) VALUES ('ALTER SESSION', 'Управления');
    INSERT INTO sql_commands(command, type) VALUES ('ALTER SYSTEM', 'Управления');
    INSERT INTO sql_commands(command, type) VALUES ('COMMIT', 'Управления');
    INSERT INTO sql_commands(command, type) VALUES ('ROLLBACK', 'Управления');
    INSERT INTO sql_commands(command, type) VALUES ('DELETE', 'DML');
    INSERT INTO sql_commands(command, type) VALUES ('INSERT', 'DML');
    INSERT INTO sql_commands(command, type) VALUES ('SELECT', 'DML');
    INSERT INTO sql_commands(command, type) VALUES ('UPDATE', 'DML');
    INSERT INTO sql_commands(command, type) VALUES ('ALTER ROLE', 'DDL');
    INSERT INTO sql_commands(command, type) VALUES ('ALTER VIEW', 'DDL');
    INSERT INTO sql_commands(command, type) VALUES ('CREATE ROLE', 'DDL');
    INSERT INTO sql_commands(command, type) VALUES ('CREATE TABLE', 'DDL');
    INSERT INTO sql_commands(command, type) VALUES ('DROP', 'DDL');
    INSERT INTO sql_commands(command, type) VALUES ('GRANT', 'DDL');
    INSERT INTO sql_commands(command, type) VALUES ('REVOK', 'DDL');
    INSERT INTO sql_commands(command, type) VALUES ('TRUNCATE', 'DDL');
";

    $dbConnection->exec($sql);
    echo 'БД успешно инициализирована';
} catch (Exception $exception) {
    echo 'Ошибка: ' . $exception->getMessage();
}



