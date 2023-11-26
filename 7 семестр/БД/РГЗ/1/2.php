<?php
    require 'dbconnection.php';
    $sql = "SELECT DISTINCT developer FROM operation_systems WHERE type = (SELECT MIN(type) FROM operation_systems);";
?>

<b>
    <?= $sql ?>
</b>

<?php

    $param = strtoupper($_GET['param']) . '%';
    $statement = $dbConnection->prepare($sql);
    $statement->execute();
    $result = $statement->fetchAll(PDO::FETCH_ASSOC);

    if ($result) {
        $columns = array_keys($result[0]);
    } else {
        echo 'Ничего не найдено';
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
