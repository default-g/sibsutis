<?php

$value = $_GET['p'] ?? null;

if (!$value) {
    echo 'Не указан параметр p';
    return;
}

$value = (int) $value;

if (!(-5 <= $value && $value <= 2)) {
    echo 'Ошибка ввода, повторите попытку';
    return;
}

if ($value < 0) {
    echo 'минус ';
}

$value = abs($value);

switch ($value) {
    case 0:
        echo 'ноль';
        return;
    case 1:
        echo 'один';
        return;
    case 2:
        echo 'два';
        return;
    case 3:
        echo 'три';
        return;
    case 4:
        echo 'четыре';
        return;
    case 5:
        echo 'пять';
        return;
    default:
        echo 'Ошибка ввода';
        return;
}
