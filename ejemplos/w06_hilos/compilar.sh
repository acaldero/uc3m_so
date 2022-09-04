#!/bin/bash
set -x

gcc -Wall -g -o ths_creatjoin ths_creatjoin.c -lpthread

gcc -Wall -g -o ths_creatsleep ths_creatsleep.c -lpthread

