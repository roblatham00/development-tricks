# ltrace: A library call tracer

Behaves a lot like strace, except it prints library calls, not system calls
(unless you pass the -S flag...).

Here's an example tracing every MPI call an application makes.  `ltrace` isn't
MPI aware, so output from multiple processes can end up jumbled together.
Instead we can use the "multiple process" syntax to give both processes a
unique output file.

```
% ~/work/soft/mpich/bin/mpiexec -np 1 ltrace -x @libmpi.so --output=cpi.ltrace.0 ./cpi : -np 1 ltrace -x @libmpi.so  -o cpi.ltrace.1 ./cpi
Process 0 of 2 is on LAPTOP-QV97NQLH
Process 1 of 2 is on LAPTOP-QV97NQLH
pi is approximately 3.1415926544231318, Error is 0.0000000008333387
wall clock time = 0.000877
% ls
README.md  cpi  cpi.c  cpi.ltrace.0  cpi.ltrace.1
% cat cpi.ltrace.1
MPI_Init(0x7fff3ea6656c, 0x7fff3ea66560, 0x7fff3ea66560, 0x557133b15d48) = 0
MPI_Comm_size(0x44000000, 0x7fff3ea66584, 2, 0xffffff) = 0
MPI_Comm_rank(0x44000000, 0x7fff3ea66580, 2, 0xffffff) = 0
MPI_Get_processor_name(0x7fff3ea665d0, 0x7fff3ea66588, 0x7fff3ea66588, 0xffffff) = 0
fprintf(0x7f292664f5c0, "Process %d of %d is on %s\n", 1, 2, "LAPTOP-QV97NQLH") = 37
fflush(0x7f292664f5c0)                           = 0
MPI_Bcast(0x7fff3ea6657c, 1, 0x4c000405, 0)      = 0
MPI_Reduce(0x7fff3ea66590, 0x7fff3ea66598, 1, 0x4c00080b) = 0
MPI_Finalize(0, 264, 2, 4)                       = 0
+++ exited (status 0) +++
```

You might have noticed that `MPI_Init` (which takes two arguments) and
`MPI_Finalize` (which takes no arguments) were shown taking four.  That's a
limitation of ltrace itself:  it will always print four values from the stack
if it did not find that routine in an ltrace prototype config file (see
https://stackoverflow.com/questions/48131925/how-does-ltrace-display-rand ) .
