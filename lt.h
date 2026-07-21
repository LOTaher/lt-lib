#ifndef LT_H
#define LT_H

/* ------ LT ------
  Utility library used by Laith Taher for all C Programming. It is meant to be imported in all C files I use and work on all systems */

#include <stdint.h>

/* --- Base Layer --- */

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef i8       b8;
typedef i32      b32;
typedef float    f32;
typedef double   f64;

#define MIN(a, b) \
    ((a) < (b) ? (a) : (b))
#define MAX(a, b) \
    ((a) > (b) ? (a) : (b))

#define KiB(n) \
    ((u64)(n) << 10)
#define MiB(n) \
    ((u64)(n) << 20)
#define GiB(n) \
    ((u64)(n) << 30)

#define ARR_LENGTH(arr) \
    (sizeof(arr) / sizeof((arr)[0]))

#define local static
#define global static
#define internal static

#define TRUE 1
#define FALSE 0

/* --- OS Library --- */

extern void* lt_os_reserve(u64 size);               // Reserve address space without physical commits.
extern b32   lt_os_commit(void* ptr, u64 size);     // Commit pages and map to physical memory.
extern void  lt_os_decommit(void* ptr, u64 size);   // Decommit pages.
extern void  lt_os_release(void* ptr, u64 size);    // Release the reservation.
extern u64   lt_os_page_size(void);                 // Check the page size of the system.

/* --- Arena Library --- */

typedef struct {
    u64 capacity;   // Reserved address space
    u64 committed;  // Backed by physical memory
    u64 pos;        // Current allocation offset
} Arena;

typedef struct {
    Arena* arena;
    u64 pos;
} Arena_Temp;

#define LT_ARENA_COMMIT_CHUNK MiB(1) // How much memory to commit at a time

extern Arena*     lt_arena_create(u64 capacity);                    // Create an Arena Allocator.
extern void       lt_arena_destroy(Arena* arena);                   // Destroy (free) an Arena.
extern u64        lt_arena_align_forward(u64 pos, u64 alignment);   // Align memory to the next power of 2.
extern void*      lt_arena_push(Arena* arena, u64 size);            // Push new memory onto the Arena.
extern void       lt_arena_clear(Arena* arena);                     // Clear the memory in an Arena.
extern u64        lt_arena_mark(Arena* arena);                      // Mark the current position in an Arena.
extern void       lt_arena_pop(Arena* arena, u64 mark);             // Pop to the memory mark of an Arena.

extern Arena_Temp lt_arena_temp_begin(Arena* arena);                // Create a Temp_Arena.
extern void       lt_arena_temp_end(Arena_Temp arena);              // Destory a Temp_Arena.

/* --- String Library --- */

typedef struct {
  u8* str;
  u64 length;
} String8;

#define lt_string_lit(s) \
    (String8){(u8 *)(s), sizeof(s) - 1}
#define lt_string_fmt(s) \
    (int)(s).length, (s).str

extern String8 lt_string_substring(String8 str, u64 start, u64 end);       // Get the substring of a given string.
extern String8 lt_string_cstring(char *str);                               // Convert a C string to a String8.
extern String8 lt_string_copy(String8 str, Arena *arena);                  // Copy a new string in memory.
extern String8 lt_string_concat(String8 str1, String8 str2, Arena *arena); // Concat two strings together.
extern b8      lt_string_compare(String8 str1, String8 str2);              // Check whether two strings are equal.
extern b8      lt_string_contains(String8 str, String8 substr);            // Check whether a string contains another.

#endif // LT_H
