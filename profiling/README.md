# Stack sampling

There are lots of profilers and visualizers out there.  You are probably
already using `perf`, `dtrace`, `cachegrind`.  But here's a fun one I learned
about a few years ago on stack overflow (
https://stackoverflow.com/a/378024/1024740 ): run it in a debugger, interrupt
the program a few times, see where you are in the backtrace.  It doesn't seem
like it should work all that well but man it kind of does!

We were trying to figure out why our performance on a new system was so much
slower than expected.  Was it the new network? Some operating system feature we
didn't take into account?

(By the way, I used the [STAT tool](https://github.com/LLNL/STAT) to produce
these visualizations but that tool is kind of a pain to set up.  It's packaged
as part of Cray's development tools, though, so the hard work might already be
done for you)

I attached to our benchmark with gdb then hit ctrl-c a few times to interrupt
the program.  Each time, I looked at the backtrace (`bt`).

It only took ten samples to find the problem:![original](quintain-before.png
"Sampled stacks before fixing") That purple `margo_destroy` path is supposed
to be fast.  Definitely should not show up in 10% of the samples, that's for
sure. Turns out we were improperly cleaning up some data structures.  Once we
fixed that, everything looked more reasonable ![fixed](quintain-fixed.png
"Sampled stacks after addressing cleanup")

