# fun with GDB

(There's a trivial Fibonacci calculator here (fib.cc) you can use to try out
this stuff, or apply it to whatever code you've got lying around)

- If you use emacs, then I suppose "Text Mode UI" is pretty good for you (gdb
  -tui).  I haven't come to love it myself.  If you use vim, try `cgdb` the
  "curses debugger" (https://cgdb.github.io/)

- Iulian Grindeanu suggested [ddd](https://www.gnu.org/software/ddd/), a
  graphical front-end to gdb.

- Let's say your program is misbehaving and you want to figure out why.  Sure
  you can `sleep(3000)` to give you time to attach to it, but here's another
  way I learned from the book _21st Century C_ :  `raise(SIGSTOP)` will make
  the program halt until you attach and continue execution under a debugger.

  ```c
  if (rank == 0) raise(SIGSTOP)
  ```

  is how I typically do it in e.g. an MPI program.  No need to mess with (or
  learn) "multi-process invocation" syntax.

- Robert Underwood wrote [mpigdb](https://github.com/robertu94/mpigdb) to make
  it even easier to interact with MPI programs.
