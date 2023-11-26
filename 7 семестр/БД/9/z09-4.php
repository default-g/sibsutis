<?php


    require_once('dbconnection.php');

    $statement = $dbConnection->query("SELECT * FROM `$baseTableName`");
    $result = $statement->fetchAll();

    session_start();

?>

<style>
    * {
        padding: 10px;
        border: 1px solid black;
        border-collapse: collapse;
    }
</style>


<form action="z09-4.php" method="post">
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
                <td><input type="radio" name="id" onclick="submit()" value="<?= $value['id'] ?>" /></td>
                <td><?= $value['name'] ?></td>
                <td><?= $value['city'] ?></td>
                <td><?= $value['address'] ?></td>
                <td><?= $value['birthday'] ?></td>
                <td><?= $value['mail'] ?></td>
            </tr>

        <?php endforeach; ?>

    </table>
</form>

<?php

    $validation_rules = [
        'name' => function($string) {
            return !empty(trim($string));
        },
        'mail' => function($string) {
            return filter_var($string, FILTER_VALIDATE_EMAIL);
        }
    ];

    if (isset($_POST['id'], $_POST['field_name'], $_POST['field_value'])) {
        $id = $_POST['id'];
        $field_name = $_POST['field_name'];
        $field_value = $_POST['field_value'];

        if (isset($validation_rules[$field_name])) {
            if(!$validation_rules[$field_name]($field_value)) {
                $_SESSION['error'] = 'Invalid field value';
                header("Location: z09-4.php");
                return;
            }
        }


        $statement = $dbConnection->prepare("UPDATE `$baseTableName` SET `$field_name` = :field_value WHERE `id` = :id");
        $statement->bindParam(':id', $id);
        $statement->bindParam(':field_value', $field_value);
        $statement->execute();

        header("Location: z09-3.php");
        return;
    }
?>
<?= $_SESSION['error'] ?? '' ?>
<?php
    unset($_SESSION['error']);
?>
<?php if(isset($_POST['id'])): ?>
    <?php
        $statement = $dbConnection->prepare("SELECT * FROM `$baseTableName` WHERE `id`=:id");
        $statement->bindParam(':id', $_POST['id']);
        $statement->execute();
        $result = $statement->fetch(PDO::FETCH_ASSOC);
        echo '<pre>';
        var_dump($result);
        echo '</pre>';
    ?>
    <form action="z09-4.php" method="post">
        <input type="hidden" name="id" value="<?= $result['id'] ?>" />
        <select name="field_name">
            <?php foreach ($result as $key => $value): ?>
                <?php if ($key !== 'id'): ?>
                    <option value="<?= $key ?>"><?= $key ?></option>
                <?php endif; ?>
            <?php endforeach; ?>
        </select>
        <input type="text" name="field_value" required/>
        <button>Заменить</button>
    </form>
<?php endif; ?>

