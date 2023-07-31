echo running time of neon_add_s32
aarch64-linux-gnu-gcc -o neon_adds32 neon_adds32_test.c ../neoncal.c
time ./neon_adds32
echo running time of add_s32 
gcc -o adds32 adds32_test.c
time ./adds32
