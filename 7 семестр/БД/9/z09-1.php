<?php

require_once('dbconnection.php');

try {

    $query = "DROP TABLE IF EXISTS `$baseTableName`; CREATE TABLE `$baseTableName` (
        `id` INTEGER PRIMARY KEY AUTOINCREMENT,
        `name` VARCHAR(50),
        `city` VARCHAR(50) ,
        `address` VARCHAR(50) ,
        `birthday` DATE ,
        `mail` VARCHAR(20) )";

    $dbConnection->exec($query);

    echo 'БД успешно создана<br />';

} catch(Exception $exception) {
    echo "Невозомжно создать БД<br />";

    echo $exception->getMessage();
    die();
}
