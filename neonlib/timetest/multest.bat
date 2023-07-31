echo running time of neon_mul_s32
gcc -o neon_muls32 neon_muls32_test.c ../neoncal.c
time ./neon_muls32
echo running time of mul_s32 
gcc -o muls32 muls32_test.c
time ./muls32

echo running time of neon_mul_s16
gcc -o neon_muls16 neon_muls16_test.c ../neoncal.c
time ./neon_muls16
echo running time of mul_s16 
gcc -o muls16 muls16_test.c
time ./muls16

echo running time of neon_mul_s8
gcc -o neon_muls8 neon_muls8_test.c ../neoncal.c
time ./neon_muls8
echo running time of mul_s8 
gcc -o muls8 muls8_test.c
time ./muls8

echo running time of neon_mul_f32
gcc -o neon_mulf32 neon_mulf32_test.c ../neoncal.c
time ./neon_mulf32
echo running time of mul_f32 
gcc -o mulf32 mulf32_test.c
time ./mulf32
