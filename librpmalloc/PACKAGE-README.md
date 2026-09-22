# librpmalloc - Cross-platform lock-free thread-caching memory allocator

This is a `build2` package for the [`rpmalloc`](https://github.com/mjansson/rpmalloc)
C library. It provides a lock-free, thread-caching, 16-byte aligned general
purpose memory allocator with a `malloc`-family API (`rpmalloc`, `rpfree`,
`rprealloc`, etc.), an optional override of the standard library's own
`malloc` family and, in C++, `new`/`delete`, and an optional first class
heap API for scoped allocations.


## Usage

To start using `librpmalloc` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: librpmalloc ^2.0.1
```

Then import the library in your `buildfile`:

```
import libs = librpmalloc%lib{rpmalloc}
```


## Importable targets

This package provides the following importable targets:

```
lib{rpmalloc}
```

Consumers include `<rpmalloc.h>` for the main allocator API. On Windows, a
consumer that wants `operator new`/`operator delete` overridden must also
`#include <rpnew.h>` in exactly one translation unit (it defines the
operators with external linkage and has no include guard); on other
platforms this happens automatically when `config.librpmalloc.override` is
enabled and `rpnew.h` must not be included.


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.librpmalloc.override         ?= true
[bool] config.librpmalloc.statistics       ?= false
[bool] config.librpmalloc.validate_args    ?= false
[bool] config.librpmalloc.asserts          ?= false
[bool] config.librpmalloc.leak_detection   ?= false
[bool] config.librpmalloc.first_class_heaps ?= false
```

`override` builds in overrides for the standard library's `malloc` family
(and, in C++, `new`/`delete` on non-Windows platforms) with automatic
process/thread initialization and finalization.

`statistics` enables collection of detailed memory page and heap statistics,
queryable with `rpmalloc_thread_statistics()`/`rpmalloc_global_statistics()`,
at a small runtime cost.

`validate_args` enables integer overflow checks on the size arguments passed
to the allocator's global entry points.

`asserts` enables internal consistency asserts.

`leak_detection` enables detection, at `rpmalloc_finalize()`, of allocations
still outstanding; requires `statistics` for the allocation counters.

`first_class_heaps` enables the explicit `rpmalloc_heap_*` API for scoped,
single-threaded heaps that can be released in one call. It gates both the
implementation and the declarations in `<rpmalloc.h>`; a consumer importing
this package automatically sees the declarations exactly when the library
was built with this variable enabled.
