load-time
=========

Mesure the time it takes to load a shared library. Only useful for benchmarking,
but that's already something!

Installation
------------

Just::

    > make

Creates the ``load-time`` binary. But really, it's just a simple source file of
a dozen of lines, so you should be able to compile it on your own on any Linux
box.

Then drop it where you want, add it to your ``PATH``, not my business.


Usage
-----

Basically::

    > load-time /path/to/a/shared/library.so
    142 us


For instance::

    > load-time /usr/lib64/libm.so.6
    142 us

Why
---

Some library takes more time to load than we would expect. There usually is a
reason, this tool is the first stone I use to understand why. For instance, an
investigation of the output of::

    > valgrind --tool=callgrind load-time /usr/lib64/libstdc++.so.6
    [...]

with ``kcachegrind`` tells me that ``std::ios_base::Init::Init()`` is the global
constructor that uses most of the ``libstdc++`` startup time on my system.

``load-time`` also tells me that it only takes a hundred of nanoseconds to load
the lib, which basically means it's probably fine :-)
