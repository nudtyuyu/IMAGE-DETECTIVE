mkdir -p ./bmp2jpeg-optimized/time
mkdir -p ./bmp2jpeg-optimized/b
mkdir -p ./bmp2jpeg-optimized/a
mkdir -p ./bmp2jpeg-optimized/img
gcc ./control_toolkit/3/gcommand.cpp -o ./control_toolkit/3/gcommand
./control_toolkit/3/gcommand
./control_toolkit/3/command.bat
python3 ./control_toolkit/3/view.py
