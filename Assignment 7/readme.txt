Akshay Bhat
5/14/2015
CS 35L - HW7
Multithreaded Performance - SRT Implementation



Before implementation:
To test that it the ray tracer worked without multithreading:

[classabh@lnxsrv01 ~/lab7/hw7/srt]$ make clean check
rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm
time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m47.909s
user    0m47.911s
sys     0m0.002s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp
./srt: Multithreading is not supported yet.

real    0m0.002s
user    0m0.000s
sys     0m0.000s
Makefile:35: recipe for target '2-test.ppm' failed
make: *** [2-test.ppm] Error 1

2-test.ppmm failed since I still hadnt implemented  multithreading.

2.
#I opened putty with X11 enabled, opened Xming.
#login with classabh.lnxsrv.seas.ucla.edu
#open the test result file with gimp

$ gimp 1-test.ppm


======================================================================================
After implementing multithreading in SRT:

There were several issues I came across during this lab:

- I was unsure how to pass the 4th argument into the pthread_create() function.
I finally decided that the best way to do it was to dynamically allocate an array
that could hold one integer value for each of the threads, thus allowing me to pass
in an x-coordinate for each thread.
-I also realized that I would have to increment the value of these pointer for each
thread, so that they would start at certain offsets, and move across the columns of pixels
without overwriting each other.
-It took me some time to realize that I would have to split the work up into processing the
image and printing it all out at once in the end.
-Overall it was very difficult to see where I went wrong, because the code was somewhat
difficult to debug and there very plenty of compiler error related to variables that
I forgot to make global, as well as segmentation faults while processing the pixels
using threads.

======================

Typing make check after implementation resulted in the following timed results:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m48.981s
user    0m48.985s
sys     0m0.000s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m25.487s
user    0m50.731s
sys     0m0.003s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m12.800s
user    0m50.600s
sys     0m0.008s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m8.573s
user    1m0.078s
sys     0m0.004s
mv 8-test.ppm.tmp 8-test.ppm

As we can see, multithreading results in significant improvements in performance.
Switching from 1 thread to 8 threads, the real time reduces by approximately a factor of 6
(the reason it doesnt improve by a factor of 8 is that time is consumed for creating the
threads, joining, etc.)
