
echo running time of neon_exp
aarch64-linux-gnu-gcc -o neon_exp_test neon_exp_test.c ../neon_exp.c
time ./neon_exp_test

echo running time of exp
g++ exp_test.cpp -o exp_test
time ./exp_test 