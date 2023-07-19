rm ./output
clang -D DEBUG  -o output main.c
./output $1 $2
