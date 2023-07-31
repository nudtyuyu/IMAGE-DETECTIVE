rm -rf ./bmp2jpeg-optimized/a
rm -rf ./bmp2jpeg-optimized/b
mkdir -p ./bmp2jpeg-optimized/b
mkdir -p ./bmp2jpeg-optimized/a
gcc ./control_toolkit/gcommand.cpp -o ./control_toolkit/gcommand
./control_toolkit/gcommand 4
