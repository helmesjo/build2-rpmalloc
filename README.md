# rpmalloc - Cross-platform lock-free thread-caching memory allocator

This is a `build2` package repository for [`rpmalloc`](https://github.com/mjansson/rpmalloc),
a cross-platform lock-free thread-caching memory allocator implemented in C.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`rpmalloc` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](librpmalloc/PACKAGE-README.md) file.

The development setup for `rpmalloc` uses the standard `bdep`-based workflow.
For example:

```
git clone .../rpmalloc.git
cd rpmalloc

bdep init -C @gcc cc config.cc=gcc
bdep update
bdep test
```
