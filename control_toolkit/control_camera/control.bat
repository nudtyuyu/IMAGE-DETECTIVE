rm ./control_toolkit/control_camera/command.bat
touch ./control_toolkit/control_camera/command.bat
chmod +x ./control_toolkit/control_camera/command.bat 
gcc ./control_toolkit/control_camera/gcommand.cpp -o ./control_toolkit/control_camera/gcommand -O3
./control_toolkit/control_camera/gcommand
./control_toolkit/control_camera/command.bat

