<?php

$var1 = 'Alice';
$var2 = "My name is $var1";
$var3 = 'My frind is $var1';
$var4 = &$var1;

echo '<pre>';
var_dump($var1, $var2, $var3, $var4);
echo '</pre>';

$var1 = 'Bob';

echo '<pre>';
var_dump($var1, $var2, $var3, $var4);
echo '</pre>';


$user = 'Michael';
$$user = 'Jackson';

var_dump($user, $Michael);
