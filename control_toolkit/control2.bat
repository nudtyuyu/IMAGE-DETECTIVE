rm -rf ./bmp2jpeg/a
rm -rf ./bmp2jpeg/b
mkdir -p ./bmp2jpeg/b
mkdir -p ./bmp2jpeg/a
gcc ./control_toolkit/gcommand.cpp -o ./control_toolkit/gcommand
./control_toolkit/gcommand 2
