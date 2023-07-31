rm -rf ./bmp2jpeg/frames-boost
mkdir -p ./bmp2jpeg/frames-boost
g++ ./control_toolkit/dark_neon.cpp -o ./control_toolkit/dark2 `pkg-config --cflags --libs opencv`


