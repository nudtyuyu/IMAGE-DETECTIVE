(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/1.jpg ./bmp2jpeg/frames-jpeg/1.bmp) >& ./bmp2jpeg/time/time_usage1
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/1.bmp -bmp ./bmp2jpeg/b/1.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/2.jpg ./bmp2jpeg/frames-jpeg/2.bmp) >& ./bmp2jpeg/time/time_usage2
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/2.bmp -bmp ./bmp2jpeg/b/2.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/3.jpg ./bmp2jpeg/frames-jpeg/3.bmp) >& ./bmp2jpeg/time/time_usage3
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/3.bmp -bmp ./bmp2jpeg/b/3.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/4.jpg ./bmp2jpeg/frames-jpeg/4.bmp) >& ./bmp2jpeg/time/time_usage4
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/4.bmp -bmp ./bmp2jpeg/b/4.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/5.jpg ./bmp2jpeg/frames-jpeg/5.bmp) >& ./bmp2jpeg/time/time_usage5
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/5.bmp -bmp ./bmp2jpeg/b/5.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/6.jpg ./bmp2jpeg/frames-jpeg/6.bmp) >& ./bmp2jpeg/time/time_usage6
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/6.bmp -bmp ./bmp2jpeg/b/6.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/7.jpg ./bmp2jpeg/frames-jpeg/7.bmp) >& ./bmp2jpeg/time/time_usage7
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/7.bmp -bmp ./bmp2jpeg/b/7.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/8.jpg ./bmp2jpeg/frames-jpeg/8.bmp) >& ./bmp2jpeg/time/time_usage8
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/8.bmp -bmp ./bmp2jpeg/b/8.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/9.jpg ./bmp2jpeg/frames-jpeg/9.bmp) >& ./bmp2jpeg/time/time_usage9
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/9.bmp -bmp ./bmp2jpeg/b/9.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/10.jpg ./bmp2jpeg/frames-jpeg/10.bmp) >& ./bmp2jpeg/time/time_usage10
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/10.bmp -bmp ./bmp2jpeg/b/10.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/11.jpg ./bmp2jpeg/frames-jpeg/11.bmp) >& ./bmp2jpeg/time/time_usage11
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/11.bmp -bmp ./bmp2jpeg/b/11.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/12.jpg ./bmp2jpeg/frames-jpeg/12.bmp) >& ./bmp2jpeg/time/time_usage12
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/12.bmp -bmp ./bmp2jpeg/b/12.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/13.jpg ./bmp2jpeg/frames-jpeg/13.bmp) >& ./bmp2jpeg/time/time_usage13
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/13.bmp -bmp ./bmp2jpeg/b/13.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/14.jpg ./bmp2jpeg/frames-jpeg/14.bmp) >& ./bmp2jpeg/time/time_usage14
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/14.bmp -bmp ./bmp2jpeg/b/14.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/15.jpg ./bmp2jpeg/frames-jpeg/15.bmp) >& ./bmp2jpeg/time/time_usage15
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/15.bmp -bmp ./bmp2jpeg/b/15.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/16.jpg ./bmp2jpeg/frames-jpeg/16.bmp) >& ./bmp2jpeg/time/time_usage16
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/16.bmp -bmp ./bmp2jpeg/b/16.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/17.jpg ./bmp2jpeg/frames-jpeg/17.bmp) >& ./bmp2jpeg/time/time_usage17
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/17.bmp -bmp ./bmp2jpeg/b/17.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/18.jpg ./bmp2jpeg/frames-jpeg/18.bmp) >& ./bmp2jpeg/time/time_usage18
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/18.bmp -bmp ./bmp2jpeg/b/18.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/19.jpg ./bmp2jpeg/frames-jpeg/19.bmp) >& ./bmp2jpeg/time/time_usage19
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/19.bmp -bmp ./bmp2jpeg/b/19.jpg
(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/20.jpg ./bmp2jpeg/frames-jpeg/20.bmp) >& ./bmp2jpeg/time/time_usage20
./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/20.bmp -bmp ./bmp2jpeg/b/20.jpg
python3 ./control_toolkit/view.py
