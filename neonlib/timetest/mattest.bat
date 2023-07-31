echo running time of neon_matmul_s32
gcc -o neon_matmul_s32 neon_matmul_s32.c ../neon_mat_cal.c
time ./neon_matmul_s32
echo running time of matmul_s32 
gcc -o matmul_s32 matmul_s32.c
time ./matmul_s32

echo running time of neon_matmul_s16
gcc -o neon_matmul_s16 neon_matmul_s16.c ../neon_mat_cal.c
time ./neon_matmul_s16
echo running time of matmul_s16 
gcc -o matmul_s16 matmul_s16.c
time ./matmul_s16

echo running time of neon_matmul_s8
gcc -o neon_matmul_s8 neon_matmul_s8.c ../neon_mat_cal.c
time ./neon_matmul_s8
echo running time of matmul_s8 
gcc -o matmul_s8 matmul_s8.c
time ./matmul_s8

echo running time of neon_matmul_f32
gcc -o neon_matmul_f32 neon_matmul_f32.c ../neon_mat_cal.c
time ./neon_matmul_f32
echo running time of matmul_f32 
gcc -o matmul_f32 matmul_f32.c
time ./matmul_f32