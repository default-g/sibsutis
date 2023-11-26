#!/bin/bash

let Y=5
let X=10
let DY=6
let DX=11
let BY=5
let BX=10

#column_address=\E[%i%p1%dG
#row_address=\E[%i%p1%dd
#cursor_up=\E[A

echo -e "\E[11m";
BOX=`echo -e "\E(0\E["$BY"d
\E[A\E["$BX"Glqqqqqqqqqk
    \E["$BX"Gx         x
    \E["$BX"Gx         x
    \E["$BX"Gx         x
    \E["$BX"Gx         x
    \E["$BX"Gx         x
    \E["$BX"Gx         x
    \E["$BX"Gmqqqqqqqqqj\E(B"`
    
DIGIT=`echo -e "\E(0\E["$DY"d
\E[A\E["$DX"G
    \E["$DX"G aa  aa   
    \E["$DX"Ga  aa  a
    \E["$DX"Ga      a 
    \E["$DX"G aa  aa
    \E["$DX"G   aa  
    \E(B"`




echo -e "\E[H\E[2J"
# echo "$BOX"
echo "$DIGIT"