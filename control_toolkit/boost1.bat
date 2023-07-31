rm -rf ./bmp2jpeg/frames-boost
mkdir -p ./bmp2jpeg/frames-boost
g++ ./control_toolkit/dark0.cpp -o ./control_toolkit/dark0 `pkg-config --cflags --libs opencv`

