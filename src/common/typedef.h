#ifndef HG_TYPEDEF
#define HG_TYPEDEF

typedef _Bool               bool;
#define true                1
#define false               0

typedef unsigned long long  size_t;
typedef signed long long    ssize_t;

typedef size_t              uintptr;
typedef ssize_t             intptr;

typedef unsigned char       u8;
typedef signed char         i8;
typedef u8                  byte;

typedef short               i16;
typedef unsigned short      u16;

typedef int                 i32;
typedef unsigned int        u32;

typedef long long int       i64;
typedef unsigned long long  u64;

typedef float               f32;
typedef double              f64;

#define nullptr(Ty)         (Ty*)0

#define ptr(Ty)             const Ty*
#define mutptr(Ty)          Ty*
#define opaque_ptr          const void*
#define opaque_mutptr       void*

#endif // !HG_TYPEDEF