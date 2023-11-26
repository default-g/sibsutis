<?php

require 'dbconnection.php';

$column = $_GET['column'];
try {
    $data = $dbConnection->query("SELECT $column FROM $tableName")->fetchAll();
} catch (Exception $e) {
    echo 'Ошибка обработки запроса';
    return;
}

?>

<style>
    * {
        border: 1px solid black;
        border-collapse: collapse;
    }
</style>
<table>
    <tr><th><?= $column ?></th></tr>
    <?php foreach ($data as $row): ?>
        <tr><td><?= $row[0] ?></td></tr>
    <?php endforeach ?>
</table>
