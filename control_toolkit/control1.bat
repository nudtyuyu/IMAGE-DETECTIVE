rm -rf ./bmp2jpeg/time
rm -rf ./bmp2jpeg/a
rm -rf ./bmp2jpeg/b
rm -rf ./bmp2jpeg/img
mkdir -p ./bmp2jpeg/time
mkdir -p ./bmp2jpeg/b
mkdir -p ./bmp2jpeg/a
mkdir -p ./bmp2jpeg/img
gcc ./control_toolkit/gcommand.cpp -o ./control_toolkit/gcommand
./control_toolkit/gcommand 1
