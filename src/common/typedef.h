#ifndef HG_TYPEDEF
#define HG_TYPEDEF

/// @brief Boolean (Either true or false)
typedef _Bool               bool;
/// @brief True (of type bool)
#define true                (bool)1
/// @brief False (of type bool)
#define false               (bool)0

/// @brief Largest unsigned integer on the platform
typedef unsigned long long  size_t;
/// @brief Largest signed integer on the platform
typedef signed long long    ssize_t;

/// @brief Unsigned integer capable of storing a pointer
typedef size_t              uintptr;
/// @brief Signed integer capable of storing a pointer
typedef ssize_t             intptr;

/// @brief Signed 8-bit integer
typedef signed char         i8;
/// @brief Unsigned 8-bit integer
typedef unsigned char       u8;
/// @brief Unsigned 8-bit integer
typedef u8                  byte;

/// @brief Signed 16-bit integer
typedef short               i16;
/// @brief Unsigned 16-bit integer
typedef unsigned short      u16;

/// @brief Signed 32-bit integer
typedef int                 i32;
/// @brief Unsigned 32-bit integer
typedef unsigned int        u32;

/// @brief Signed 16-bit integer
typedef long long int       i64;
/// @brief Unsigned 64-bit integer
typedef unsigned long long  u64;

/// @brief 32-bit IEEE floating point
typedef float               f32;
/// @brief 64-bit IEEE floating point
typedef double              f64;

/// @brief nullptr of type 'Ty'
#define nullptr(Ty)         (Ty*)0

/// @brief Pointer of type 'const Ty'
#define ptr(Ty)             const Ty*
/// @brief Pointer of type 'Ty' (mutable)
#define mutptr(Ty)          Ty*
/// @brief Pointer of type 'const void*'
#define opaque_ptr          const void*
/// @brief Pointer of type 'void*' (mutable)
#define opaque_mutptr       void*

#endif // !HG_TYPEDEF