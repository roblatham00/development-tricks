# The Shell and various command line utilities

So much to cover here... you're going to spend a lot of time in a terminal
typing shell commands, so you may as well learn how to use it and how to make
it more comfortable.


## Configuring the shell itself

You've got an account on a brand new machine... now you have to set it up just
the way you like it.

I use the ZSH shell (which invariably causes problems on other systems but
that's a different topic).  I like this approach I learned from Debian.

My `.zshrc` has almost nothing: just a loop to source the actual contents

```zsh
#!/bin/zsh

set -eu

for RC in _*; do
	. ./$RC
done
```

That's the whole thing.  I have `_env`, `_prompt`, `_alias`, and `_completion`
files that take care of settings I want on every instance.

How about platform-specific settings?  Most of the time you can use `hostname`,
though it doesn't always behave the way I'd like it to on every machine.

```
% hostname -s
ilogin3
% hostname -d
lcrc.anl.gov

SITE_ENV=~/.zsh/env.$(hostname -d)
LOCAL_ENV=~/.zsh/env.`hostname -s`
[ -f $SITE_ENV ] && . $SITE_ENV
[ -f $LOCAL_ENV ] && . $LOCAL_ENV
```

### Git and shell prompts

`PS1` is the shell variable describing how the shell should display your prompt

The `git-prompt.sh` script comes from git's
[contrib/completion/](https://github.com/git/git/tree/master/contrib/completion)
directory.  Quite a few settings to tweak the output but here's what I like:

```
source ${HOME}/.bash/git-prompt.sh
export GIT_PS1_SHOWDIRTYSTATE=yes
export GIT_PS1_SHOWSTASHSTATE=yes
export GIT_PS1_SHOWUPSTREAM=auto
export GIT_PS1_SHOWCONFLICTSTATE=yes
export GIT_PS1_SHOWCOLORHINTS=yes

export PS1='[\u@\h \W$(__git_ps1 " (%s)")]\$ '
```



## Writing Shell scripts

- add `set -eu` at the top of your scripts

--  '-e': exit if you encounter an error in a command (or pipeline of
          commands).  Otherwise, the shell script will just keep churning along
          wasting your time -- you probably did not want that command on on
          line 5 to error out, right?
--  '-u': unset variables expand to just plain old "".   You probably meant to
          type $HOME not $HMOE, right?  So catch that error right away before  you try to
          delete that custom build of ls you installed in your home directory with `rm -rf ${HMOE}/bin/ls`

## symlink order

Years ago at my first internship I was working in the computer lab and muttered
"man I never remember the order to `ln`".  I guess I muttered louder than I
thought because the old timer three rows over heard me and hollered "REAL THING
FAKE THING" and I have never forgotten the order since.

## awk

Before python, before Perl... there was awk!  It's worth reading
https://www.gnu.org/software/gawk/manual/ but here are a few things I find
myself using awk to accomplish:

### Every nth line

Let's say you've got a benchmark and it outputs data in multiple lines.
Furthermore, you're running this benchmark repeatedly so you've got lots of
lines but you only want every 5th line.  Awk has a few special variables.  One
of them, `NR` is the "number of records" variable.  Typically "number of lines"

```
% head -50 /usr/share/dict/words
A
AA
AAA
... (a bunch of lines omitted)
ASCII's
ASCIIs
% head -50 /usr/share/dict/words | awk '{if (NR%5 == 0) print NR " " $1}'
5 AB
10 ABM's
15 ACLU's
20 AF
25 AIDS
30 AL
35 AM's
40 AOL
45 AP's
50 ASCIIs
```

### Sum a column of numbers

Awk has the somewhat strange feature of a "BEGIN" and "END" block (ok there's a lot strange about awk...).   Consider this little shell fragment that produces the first ten squares:

```
% for i in `seq 1 10`; do
echo $i $((i*i))
done
1 1
2 4
3 9
4 16
5 25
6 36
7 49
8 64
9 81
10 100
```

We can simply add up every number in the 2nd column.  Lines are tokenized by
whitespace by default.  $0 is the whole line.  $2 is the 2nd token.  We only
care about the sum at the end and don't need to print it out after every line.
The 'END' block runs after all the input is processed:

```
for i in `seq 1 10`; do
echo $i $((i*i))
done | awk '{ sum += $2 }; END { print sum}'
385
```

### Median

Median is a little harder: you've got to store every item and keep track of how
many items you've seen (you can use `length()` to get the size of the array but
if you aren't using GNU awk it might not support it).  Just complicated enough
that you *could* put it in one long command line but it's better off as its own
awk program file:

```awk
% cat input.in
1
2
3
4
% cat median.awk
#!/usr/bin/awk --lint
{
        array[NR]=$1;
}
END {
        if (NR % 2) {
                print (array[ (NR+1)/2 ]);
        } else {
                print( array[ (NR/2) ] + array[ (NR/2)+1 ]) / 2.0
        }
}
% awk -f median.awk < input.in
2.5
```
