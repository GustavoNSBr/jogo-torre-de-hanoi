#!/bin/bash

gcc ./functions/functions.c ./functions/menu.c ./main.c -o main

if [ $? -eq 0 ]; then
    clear
    ./main
else
    echo Erro ao compilar o programa
fi

read