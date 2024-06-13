# text searching

We can search code with things like ctags, cscope, or clangd but sometimes you
need to search more generally.  You can get pretty far with good ol' reliable
`grep` but here are a few other tools in the same spirit.

## recursive grep

classic grep has a `-R` flag to recursively descend through a directory tree.
Watch out for binary blobs, though!

## git grep

In a git repository you can `git grep` to search just those files that are in
git revision control

## rip-grep

The [ripgrep](https://github.com/BurntSushi/ripgrep) tool aims to be a faster
grep.  It's implemented in Rust.  recursive by default, can search through
archives, and skips anything listed in your .gitignore
