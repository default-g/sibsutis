<?php
    require 'dbconnection.php';
    $sql = "SELECT DISTINCT type FROM operation_systems WHERE developer IN (SELECT developer FROM operation_systems WHERE name NOT LIKE :param)";
?>

<b>
    <?= $sql ?>
</b>

<?php

    if (isset($_GET['param']) && !empty($_GET['param'])) {
        $param = '%' . strtoupper($_GET['param']) . '%';
        $statement = $dbConnection->prepare($sql);
        $statement->bindParam(':param', $param);
        $statement->execute();
        $result = $statement->fetchAll(PDO::FETCH_ASSOC);
        if ($result) {
            $columns = array_keys($result[0]);
        } else {
            echo 'Ничего не найдено';
        }


    }
?>

<?php if(isset($result) && !empty($result)): ?>
    <table>
        <tr>
            <?php foreach($columns as $column): ?>
                <th><?= $column ?></th>
            <?php endforeach ?>
        </tr>
        <?php foreach($result as $row): ?>
            <tr>
                <?php foreach($columns as $column): ?>
                    <td><?= $row[$column] ?></td>
                <?php endforeach ?>
            </tr>
        <?php endforeach ?>
    </table>
<?php endif ?>

<form action="3.php" method="get">
    <input type="text" name="param">
    <input type="submit">
</form>
