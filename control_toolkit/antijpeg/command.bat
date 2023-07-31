cp ./antiedit/from/IndianMissile.jpg ./antiedit/from/display.jpg
./jpeg-6b/djpeg -bmp -outfile ./antiedit/from/display.bmp ./antiedit/from/display.jpg
./control_toolkit/antijpeg/sjpeg ./antiedit/from/display.bmp ./antiedit/from/display.txt
mv ./antiedit/from/display.txt ./control_toolkit/antijpeg/TEST_1/display.txt
./control_toolkit/antijpeg/realanti
./control_toolkit/antijpeg/changebmp
