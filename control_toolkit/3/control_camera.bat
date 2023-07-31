mkdir ../camera/frames
g++ Capture_bmp.cpp -o bmp `pkg-config --cflags --libs opencv4`
./bmp

