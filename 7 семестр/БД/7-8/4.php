<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $align = $_POST["align"];
    $valign = implode(" ", $_POST["valign"]);
    echo "<table>\n";
    echo "<tr>\n";
    echo "<td height=\"300\" width=\"300\" align=\"$align\" valign=\"$valign\">ТЕКСТ</td>\n";
    echo "</tr>\n";
    echo "</table>\n";
  }
?>

<form method="post">
  <p>Горизонтальное выравнивание:</p>
  <input type="radio" name="align" value="left" checked>Лево<br>
  <input type="radio" name="align" value="center">Центр<br>
  <input type="radio" name="align" value="right">Право<br>
  <p>Вертикальное выравнивание:</p>
  <input type="checkbox" name="valign[]" value="top" checked>Верх<br>
  <input type="checkbox" name="valign[]" value="middle">Середина<br>
  <input type="checkbox" name="valign[]" value="bottom">Низ<br>
  <br>
  <input type="submit" value="Выполнить">
</form>


