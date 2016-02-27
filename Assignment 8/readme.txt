
For this homework, it first looks intimidating. After close analysis of main.c, 
I realized this homework could be done by making only a few modifications.

First, I moved the code that take cares of ploting the image out of the main
function and named the function as multithreading. Since the idea of ploting a 
image is to represent each pixel as a element of a 2-D array, we can now split 
rows of the 2-D array into multiple threads and combine it later. 

(e.g: If we want to divide the task into 4, we can first assign row0, row4, ...
row(4*i) to thread1; row1, row5, ... row(4*i+1) to thread2; row2, row6, ... row
(4*i+2) to thread3; row3, row7, ... row(4*i+3) to thread4)

Then I added the code pthread_create and pthread_join to main fucntion provided 
by TAs and remove the error message when nthreads passed in not equals to 1 in 
the main function.

Lastly, I include the dependency libraries lpthread in the Makefile before make.
During make, I encountered Error 139 caused by segmentation fault. I then found
out that error is caused by mistakenly cast type (int) to (int*) as an argument
of the multithreading function. After modification, the build succeded and the results are:

1 tread:
	real	0m49.671s
	user	0m49.671s
	sys	0m0.004s

2 threads:
	real	0m25.442s
	user	0m50.644s
	sys	0m0.004s

4 threads:
	real	0m12.744s
	user	0m50.641s
	sys	0m0.002s

8 threads:
	real	0m9.697s
	user	1m7.338s
	sys	0m0.006s

We can see clearly that multithreading improves performance significantly.