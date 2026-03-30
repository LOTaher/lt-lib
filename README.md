# lt-lib

A collection of C libraries I use in my C projects. All libraries are dependent on `lt_base.h` as it is the base layer.

Inspired by RJF and the [RAD Debugger](https://github.com/EpicGamesExt/raddebugger) base libraries.

Current list of libraries:
- `lt_base.h`: Base layer of all my C projects. Includes helpful type definitions and macros.
- `lt_arena.h`: Extremely simple implementation of an arena allocator.

```c
// Arena Usage Example

#include <stdio.h>
#define LT_ARENA_IMPLEMENTATION
#include "lt_arena.h"

int main(void) {
    // Create an arena with 10 MiB of backing memory
    mem_arena* arena = arena_create(MiB(10));

    if (!arena) {
        return 1;
    }

    // Allocate 1 MiB from the arena
    char* buffer = (char*)arena_push(arena, MiB(1));
    if (!buffer) {
        arena_destroy(arena);
        return 1;
    }

    // Use the memory like normal heap memory
    buffer[0] = 'l';
    buffer[1] = 't';
    buffer[2] = '\0';

    printf("Buffer contains: %s\n", buffer);

    // Free all arena allocations at once
    arena_destroy(arena);

    return 0;
}
```

- `lt_strings.h`: Length based strings and common string functions. `lt_arena` is required for some functions.

```c
// Length Based Strings Usage Example.

#include <stdio.h>
#define LT_ARENA_IMPLEMENTATION
#include "lt_arena.h"
#define LT_STRING_IMPLEMENTATION
#include "lt_strings.h"

int main(void) {
    mem_arena* arena = arena_create(MiB(10));

    string8 str = str8_lit("hello");

    // Null terminated character is inferred here
    char* cStr = "hello";

    string8 str8Version = str8_cstring(cStr);

    s8 isSame = str8_compare(str, str8Version);
    if (!isSame) {
        printf("%.*s is not the same as %.*s\n", str8_fmt(str), str8_fmt(str8Version));
        return 1;
    }

    // Dynamic operations require an arena
    string8 bothStrings = str8_concat(str, str8Version, arena);

    printf("Here are both strings concatted together: %.*s\n", str8_fmt(bothStrings));
    printf("The length of this string is: %llu\n", bothStrings.length);

    // Allocated strings die with the lifetime
    arena_destroy(arena);

    return 0;
}
```

All of lt-lib's functionality is subject to change without any notice. Updates will remain backwards compatible.
