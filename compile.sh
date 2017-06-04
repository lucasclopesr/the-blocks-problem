#!/bin/bash
cd src
gcc -c Pile.c -o ../output/Pile.o
gcc -c TP1.c -o ../output/TP1.o
cd ../output/
gcc -o TP1.exe TP1.o