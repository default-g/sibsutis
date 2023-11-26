<?php

$color = $argv[0] ?? 'blue';
$size = $argv[1] ?? '28';

$text = 'Hello, world!';

echo "<span style='color: $color; font-size: $size;'>$text</span>";
