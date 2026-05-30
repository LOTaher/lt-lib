# lt-lib

A collection of C libraries I use in my C projects. All libraries are dependent on `lt_base.h` as it is the base layer.

Inspired by RJF and the [RAD Debugger](https://github.com/EpicGamesExt/raddebugger) base libraries.

Current list of libraries:

- `lt_base.h`: Base layer of all my C projects. Includes helpful type definitions and macros.
- `lt_arena.h`: Extremely simple implementation of an arena allocator.
- `lt_strings.h`: Length based strings and common string functions. `lt_arena` is required for some functions.

All of lt-lib's functionality is subject to change without any notice. Updates will remain backwards compatible.
