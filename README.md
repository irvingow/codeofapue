This repo stores some codes of apue, these codes have less comments
for the reason that I have just read csapp, so some codes become easier
to understand.

I also write a makefile for codes of apue to make it easier to compile 
and run the code in the book. For example, we have a c file named 
sample.c, if this is the first time we want to compile and run the code,
 we should first type
> gcc -c apue.c

to generate apue.o, then we can just type
> make sample

in the command line, then the execute file `sample` will be generated automatic, the we can
type
> ./sample

to run the code we have written.
In addition, I add **-g** argument to generate executable file to be debugged with gdb.
