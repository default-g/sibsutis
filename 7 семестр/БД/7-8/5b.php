<?php

$otv = [
    'dot-question' => 2,
    'ampersant-qustion' => 2,
    'checkbox-radio-question' => 2,
    'get-post-difference' => 2,
    'reverse-sort' => 2,
    'php-support' => 2,
    'world-war' => 1,
    'echo' => 1,
];

$right_answers_count = 0;

foreach ($otv as $key => $value) {
    if ($_POST[$key] == $otv[$key]) {
        $right_answers_count++;
    }
}

echo 'Результат<br/>';
echo $_POST['name'] . ': ' . ($right_answers_count . '/' . count($otv));
