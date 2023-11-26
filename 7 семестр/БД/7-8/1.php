<?php

$treug = [];
for ($n = 1; $n <= 10; $n++) {
    $treug[$n] = $n * ($n + 1) / 2;
}

echo '<pre>';
foreach ($treug as $value) {
    echo $value . '  ';
}
echo '</pre>';

$kvd = [];
for ($n = 1; $n <= 10; $n++) {
    $kvd[] = $n * $n;
}

echo '<pre>';
foreach ($kvd as $value) {
    echo $value . ' ';
}
echo '</pre>';

$rez = array_merge($treug, $kvd);

echo '<pre>';
print_r($rez);
echo '</pre>';

sort($rez);

echo '<pre>';
print_r($rez);
echo '</pre>';


array_shift($rez);

echo '<pre>';
print_r($rez);
echo '</pre>';

$rez1 = array_unique($rez);

echo '<pre>';
print_r($rez1);
echo '</pre>';
