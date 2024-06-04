# screen(1) and tmux(1)

These "screen managers" are so useful I almost forgot to mention them -- they
are as essential to me now as 'ls'.

Two important features:
* ability to detach and resume session
* searchable scrollback

I learned `screen` first and while the commands and interfaces are almost
identical, `tmux` is just different enought that I always end up switching back
to `screen`.

My tpical use case:  log into some supercomputer, start screen, then go home
for the day.  Come back later and that ssh session may have timed out but once
I log back in I can "re-attach" and pick up where I left off.


## debugging with tmux

Tom Peterka likes the [tmux](https://github.com/Azrael3000/tmpi) script:  it
can help you run an MPI program in a tiled `tmux` session.
