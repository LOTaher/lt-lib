/*  lt_arena.h - Definitions for my arena allocator implementation
    Copyright (C) 2026 splatte.dev

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#ifndef LT_ARENA_H
#define LT_ARENA_H

#include "lt_base.h"

/* API Definitions */
typedef struct {
    u64 capacity;
    u64 pos;
} arena;

typedef struct {
    arena* arena;
    u64 pos;
} arena_temp;

arena*     arena_create(u64 capacity);
void       arena_destroy(arena* arena);
u64        arena_align_forward(u64 pos, u64 alignment);
void*      arena_push(arena* arena, u64 size);
void       arena_clear(arena* arena);
u64        arena_mark(arena* arena);
void       arena_pop(arena* arena, u64 mark);

arena_temp arena_temp_begin(arena* arena);
void       arena_temp_end(arena_temp arena);

#endif // LT_ARENA_H
