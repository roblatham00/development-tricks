# Tracing programs

While you can alway manually stuff instrumentation into your functions, our
programs do not run in a vaccum.  Here are some tools that can help you
understand better what is going on with your program and any dependencies your
program might be calling.

## ltrace: A library call tracer

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

I've added a few function descriptions in `libmpi.so.conf`, and you can see how
that cleans up the output a little bit:  now you can see `MPI_COMM_WORLD`
(0x44000000), the return values of size and rank, and the proper number of
argments to finalize

```
% ~/work/soft/mpich/bin/mpiexec -np 1 ltrace -F libmpi.so.conf -x @libmpi.so --output=cpi.ltrace.0 ./cpi : -np 1 ltrace -F libmpi.so.conf -x @libmpi.so -o cpi.ltrace.1 ./cpi
Process 0 of 2 is on LAPTOP-QV97NQLH
Process 1 of 2 is on LAPTOP-QV97NQLH
pi is approximately 3.1415926544231318, Error is 0.0000000008333387
wall clock time = 0.002247
[0] LAPTOP-QV97NQLH:~/work/presentations/development-tricks/ltrace (main *=)% cat cpi.ltrace.1
MPI_Init(1, "./cpi")                             = 0
MPI_Comm_size(0x44000000, 2)                     = 0
MPI_Comm_rank(0x44000000, 1)                     = 0
MPI_Get_processor_name("LMNOPQRSTUVWXYZ[\\]^_`abcdefghijk"..., 15) = 0
fprintf(0x7f0469afd5c0, 0x56225bfa6010, 1, 2)    = 37
fflush(0x7f0469afd5c0, 0x7fff9d12c250, 0, 0)     = 0
MPI_Bcast(0x7fff9d12c41c, 1, 1275069445, 0, 0x44000000) = 0
MPI_Reduce(0x7fff9d12c430, 0x7fff9d12c438, 1, 1275070475, 1476395011, 0, 0x44000000) = 0
MPI_Finalize()                                   = 0
+++ exited (status 0) +++
```

## uftrace

[uftrace](https://github.com/namhyung/uftrace) looks pretty slick, providing
not just a text dump of what's called, but also tools to visualize the
information.

## bpftrace

Linux (since the 4.x series) has a sophisticated tracing/instrumentation
language called 'eBPF'.  [bpftrace](https://github.com/bpftrace/bpftrace).  It
is perhaps challenging to use on HPC systems.
