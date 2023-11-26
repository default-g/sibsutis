<?php

require_once('dbconnection.php');

$statement = $dbConnection->query("SELECT * FROM `$baseTableName`");
$result = $statement->fetchAll();

?>
<style>
    * {
        padding: 10px;
        border: 1px solid black;
        border-collapse: collapse;
    }
</style>

<table>
    <tr>
        <td>ID</td>
        <td>Имя</td>
        <td>Город</td>
        <td>Адрес</td>
        <td>Дата рождения</td>
        <td>E-mail</td>
    </tr>
    <?php foreach ($result as $value): ?>
        <tr>
            <td><?= $value['id'] ?></td>
            <td><?= $value['name'] ?></td>
            <td><?= $value['city'] ?></td>
            <td><?= $value['address'] ?></td>
            <td><?= $value['birthday'] ?></td>
            <td><?= $value['mail'] ?></td>
        </tr>

    <?php endforeach; ?>

</table>
