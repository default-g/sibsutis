<?php

function get_structure_of_table($tableName)
{
    global $dbConnection;
    $result = $dbConnection
        ->query("PRAGMA table_info($tableName)")
        ->fetchAll(PDO::FETCH_ASSOC);

    return $result;
}


function vid_content($tableName)
{
    global $dbConnection;

    echo "<h1>Содержимое $tableName</h1>";

    $results = $dbConnection
        ->query("SELECT * FROM `$tableName`")
        ->fetchAll(PDO::FETCH_ASSOC);

    $structure = get_structure_of_table($tableName);

    ?>
    <table>
        <tr>
            <?php foreach($structure as $column): ?>
                <td><?=  $column['name'] ?></td>
            <?php endforeach; ?>
        </tr>
        <?php foreach($results as $row): ?>
            <tr>
                <?php foreach($row as $value): ?>
                    <td><?= $value ?></td>
                <?php endforeach; ?>
            </tr>
        <?php endforeach; ?>
    </table>
    <?php

}


function vid_structure($tableName)
{
    echo "<h1>Структура $tableName</h1>";
    $result = get_structure_of_table($tableName);

    $output = [];
    foreach ($result as $column) {
        $output_for_column = $column['type'] . ' '
            . $column['name'] . ' '
            . (!$column['notnull'] ? 'NULLABLE' : 'NOT NULL') . ' '
            . ($column['pk'] ? 'PRIMARY KEY' : '');

        $output[] = $output_for_column;
    }

    echo '<pre>';
    var_dump($output);
    echo '</pre>';

}


if (!$_POST) {
    echo 'Ошибка - ничего не выбрано';
    return;
}

foreach($_POST as $table => $value) {

    if (isset($_POST[$table]['content'])) {
        vid_content($table);
    }

    if (isset($_POST[$table]['structure'])) {
        vid_structure($table);
    }

}
