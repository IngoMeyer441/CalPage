#!/bin/bash
gcc -o calpage.out *.c -D CREATE_PDF `pkg-config --cflags --libs librsvg-2.0 cairo-pdf`
