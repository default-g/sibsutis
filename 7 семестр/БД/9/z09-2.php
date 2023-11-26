<?php
    if (!empty($_POST)) {

        require_once('dbconnection.php');

        $validation_rules = [
            'name' => function($string) {
                return !empty(trim($string));
            },
            'mail' => function($string) {
                return filter_var($string, FILTER_VALIDATE_EMAIL);
            }
        ];

        foreach ($_POST as $key => $value) {
            if (isset($validation_rules[$key])) {
                if (!$validation_rules[$key]($value)) {
                    $_POST['error'] = 'Ошибка в поле ' . $key;
                }

            }
        }

        $name = $_POST['name'];
        $city = $_POST['city'];
        $address = $_POST['address'];
        $birthday = $_POST['birthday'];
        $mail = $_POST['mail'];

        $query = "INSERT INTO `$baseTableName` (`name`, `city`, `address`, `birthday`, `mail`)
            VALUES ('$name', '$city', '$address', '$birthday', '$mail')";

        $dbConnection->exec($query);
    }

?>

<?php if(isset($_POST['error'])): ?>
    <?= $_POST['error'] ?>
<?php endif ?>
<form action="z09-2.php" method="post">
    <label for="name">Имя</label>
    <input type="text" name="name" required />
    <br />
    <label for="city">Город</label>
    <input type="text" name="city" />
    <br />
    <label for="address">Адрес</label>
    <input type="text" name="address" />
    <br />
    <label for="birthday">Дата рождения</label>
    <input type="date" name="birthday" max="<?php echo date('Y-m-d'); ?>" />
    <br />
    <label for="mail">E-mail</label>
    <input type="email" name="mail" required />
    <button>Отправить</button>
</form>
