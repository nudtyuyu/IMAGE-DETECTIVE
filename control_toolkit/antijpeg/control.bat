gcc ./control_toolkit/antijpeg/gcommand.cpp -o ./control_toolkit/antijpeg/gcommand -O6
g++ ./control_toolkit/antijpeg/ssejpeg.cpp -o ./control_toolkit/antijpeg/sjpeg -O3
g++ -o ./control_toolkit/antijpeg/realanti ./control_toolkit/antijpeg/realanti.cpp ./neonlib/neoncal.c -O3
g++ -o ./control_toolkit/antijpeg/changebmp ./control_toolkit/antijpeg/changebmp.cpp -O3
./control_toolkit/antijpeg/gcommand
./control_toolkit/antijpeg/command.bat
