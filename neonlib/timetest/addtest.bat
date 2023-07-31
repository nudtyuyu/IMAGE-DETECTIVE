echo running time of neon_add_s32
gcc -o neon_adds32 neon_adds32_test.c ../neoncal.c
time ./neon_adds32
echo running time of add_s32 
gcc -o adds32 adds32_test.c
time ./adds32

echo running time of neon_add_s16
gcc -o neon_adds16 neon_adds16_test.c ../neoncal.c
time ./neon_adds16
echo running time of add_s16 
gcc -o adds16 adds16_test.c
time ./adds16

echo running time of neon_add_s8
gcc -o neon_adds8 neon_adds8_test.c ../neoncal.c
time ./neon_adds8
echo running time of add_s8 
gcc -o adds8 adds8_test.c
time ./adds8

echo running time of neon_add_s64
gcc -o neon_adds64 neon_adds64_test.c ../neoncal.c
time ./neon_adds64
echo running time of add_s64 
gcc -o adds64 adds64_test.c
time ./adds64

echo running time of neon_add_f32
gcc -o neon_addf32 neon_addf32_test.c ../neoncal.c
time ./neon_addf32
echo running time of add_f32 
gcc -o addf32 addf32_test.c
time ./addf32
