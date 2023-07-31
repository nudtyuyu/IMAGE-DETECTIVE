rm -rf ./bmp2jpeg-optimized/time
rm -rf ./bmp2jpeg-optimized/a
rm -rf ./bmp2jpeg-optimized/b
rm -rf ./bmp2jpeg-optimized/img
mkdir -p ./bmp2jpeg-optimized/time
mkdir -p ./bmp2jpeg-optimized/b
mkdir -p ./bmp2jpeg-optimized/a
mkdir -p ./bmp2jpeg-optimized/img
gcc ./control_toolkit/gcommand.cpp -o ./control_toolkit/gcommand
./control_toolkit/gcommand 3
