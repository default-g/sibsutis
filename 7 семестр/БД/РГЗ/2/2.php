<?php

require 'dbconnection.php';

function getTableStructure($tablename, $dbconnection) {
    return $dbconnection
        ->query("PRAGMA table_info($tablename)")
        ->fetchAll();
}


function getTableColumnNames($tablename, $dbconnection) {
    return array_map(
        fn ($item) => $item['name'],
        getTableStructure($tablename, $dbconnection)
    );
}

?>

<form action="3.php" method="get">
    <?php foreach(getTableColumnNames($tableName, $dbConnection) as $column): ?>
        <input type="radio" name="column" value="<?= $column ?>"><?= $column ?></input>
    <?php endforeach ?>
    <input type="submit">
</form>
