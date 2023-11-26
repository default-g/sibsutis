<?php

$cust = [
    'cnum' => 2001,
    'cname' => 'Hoffman',
    'city' => 'London',
    'snum' => '1001',
    'rating' => '100',
];

foreach ($cust as $key => $value) {
    echo $key . ' - ' . $value . '<br>';
}

echo '<br>';

asort($cust);

foreach ($cust as $key => $value) {
    echo $key . ' - ' . $value . '<br>';
}

echo '<br>';

ksort($cust);

foreach ($cust as $key => $value) {
    echo $key . ' - ' . $value . '<br>';
}

echo '<br>';

sort($cust);

foreach ($cust as $key => $value) {
    echo $key . ' - ' . $value . '<br>';
}
