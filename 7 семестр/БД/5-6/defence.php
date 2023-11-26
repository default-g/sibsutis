<?php

function print_text($text, $color) {
    echo "<span style='color:$color'>$text</span>";
}


function Ru($color) {
    print_text('Здравствуйте!', $color);
}

function En($color) {
    print_text('Hello!', $color);
}

function Fr($color) {
    print_text('Bonjour!', $color);
}

function De($color) {
    print_text('Guten Tag!', $color);
}

$lang = function($lang, $color) {
    switch ($lang) {
        case 'ru':
            Ru($color);
            break;
        case 'en':
            En($color);
            break;
        case 'fr':
            Fr($color);
            break;
        default:
            De($color);
            break;
    }
};


$language = $_GET['lang'] ?? null;

if (!$language) {
    echo 'No lang';
    die();
}

$color = $_GET['color'] ?? null;

if (!$color) {
    echo 'No color';
    die();
}

$lang($language, $color);
