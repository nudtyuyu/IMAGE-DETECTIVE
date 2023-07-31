mkdir -p ./camera/frames
g++ ./control_toolkit/control_camera/Capture_bmp.cpp -o ./control_toolkit/control_camera/bmp `pkg-config opencv --cflags --libs` -O3
./control_toolkit/control_camera/bmp

