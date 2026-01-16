# lt-lib

A collection of C libraries I use in my C projects.

**NOTE:** all libraries are dependent on `lt_base.h` as this is the base layer.

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

All of lt-lib's functionality is subject to change without any notice. Updates will remain backwards compatible.
