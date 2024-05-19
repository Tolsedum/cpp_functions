<?php

$str = "";
if($argc > 0){
    for ($i = 0; $i < $argc; $i++) {
        if($argv[$i] == "-str"){
            $str = $argv[++$i];
            break;
        }
    }
}

echo md5($str);
