<?php

echo '<style>';
echo 'table, td, th {border: 1px solid black; border-collapse: collapse;}';
echo '</style>';

echo '<table>';
$i = 1;
while ($i <= 10) {
    $j = 1;
    echo '<tr>';
    while($j <= 10) {
        $backgroundColor = 'white';
        if ($i === $j) {
            $backgroundColor = 'grey';
        }
        echo '<td style="padding:5px; background-color: ' . $backgroundColor . '">';
        echo $i * $j;
        echo '</td>';
        $j++;
    }
    echo '</tr>';
    $i++;
}
echo '</table>';
