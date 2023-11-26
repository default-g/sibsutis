<?php


echo '<style>';
echo 'table, td, th {border: 1px solid black; border-collapse: collapse;}';
echo 'td, th {width: 14px; height: 15px;}';
echo '</style>';

echo '<table>';
$i = 1;
while ($i <= 30) {
    $j = 1;
    echo '<tr>';
    while($j <= 30) {
        $backgroundColor = match (($i * $j) % 7) {
            0 => 'white',
            1 => 'aqua',
            2 => 'blue',
            3 => 'yellow',
            4 => 'purple',
            5 => 'red',
            6 => 'lime',
        };

        echo '<td style="padding:5px; background-color: ' . $backgroundColor . '">';
        echo '&nbsp';
        echo '</td>';
        $j++;
    }
    echo '</tr>';
    $i++;
}
echo '</table>';
