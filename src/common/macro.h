#ifndef __HG_MACRO
#define __HG_MACRO

/// @brief Forces inlining of a function
#define FORCE_INLINE __attribute__((always_inline)) inline
/// @brief Forces never inlining of a function
#define NEVER_INLINE __attribute__((noinline))
/// @brief Marks a variable as used
#define USED_VAR     __attribute__((__used__))
/// @brief Warns if the return value of a function is unused
#define NO_DISCARD   __attribute__ ((warn_unused_result))

/// @brief Returns the byte offset of a member in a type
#define offsetof(ty, member) __builtin_offsetof(ty, member)
/// @brief Assertion that happens at compile time
#define static_assert(boolean, message) _Static_assert(boolean, message)

#ifdef COLTPI_DEBUG
  #define COLTPI_CONFIG "Debug"
#else
  #define COLTPI_CONFIG "Release"
#endif

/// @brief Necessary macro for CONCAT
#define __DETAILS__CONCAT(a, b) a##b
/// @brief Concatenate two identifiers
#define CONCAT(a, b) __DETAILS__CONCAT(a,b)
/// @brief Concatenate three identifiers
#define CONCAT3(a, b, c) CONCAT(CONCAT(a, b), c)
/// @brief Concatenate four identifiers
#define CONCAT4(a, b, c, d) CONCAT(CONCAT3(a, b, c), d)

/**************************************
 * UGLY CODE BELOW TO FOR FOR_EACHnARG
 **************************************/

#define __DETAILS__PARENS ()
#define __DETAILS__EXPAND(...)  __DETAILS__EXPAND4(__DETAILS__EXPAND4(__DETAILS__EXPAND4(__DETAILS__EXPAND4(__VA_ARGS__))))
#define __DETAILS__EXPAND4(...) __DETAILS__EXPAND3(__DETAILS__EXPAND3(__DETAILS__EXPAND3(__DETAILS__EXPAND3(__VA_ARGS__))))
#define __DETAILS__EXPAND3(...) __DETAILS__EXPAND2(__DETAILS__EXPAND2(__DETAILS__EXPAND2(__DETAILS__EXPAND2(__VA_ARGS__))))
#define __DETAILS__EXPAND2(...) __DETAILS__EXPAND1(__DETAILS__EXPAND1(__DETAILS__EXPAND1(__DETAILS__EXPAND1(__VA_ARGS__))))
#define __DETAILS__EXPAND1(...) __VA_ARGS__

#define __DETAILS__FOR_EACH_HELPER(macro, a1, ...) \
  macro(a1) \
  __VA_OPT__(__DETAILS__FOR_EACH_AGAIN __DETAILS__PARENS (macro, __VA_ARGS__))
#define __DETAILS__FOR_EACH_AGAIN() __DETAILS__FOR_EACH_HELPER

#define __DETAILS__FOR_EACH_HELPER_1ARG(macro, arg, a1, ...) \
  macro(arg, a1) \
  __VA_OPT__(__DETAILS__FOR_EACH_AGAIN_1ARG __DETAILS__PARENS (macro, arg, __VA_ARGS__))
#define __DETAILS__FOR_EACH_AGAIN_1ARG() __DETAILS__FOR_EACH_HELPER_1ARG

#define __DETAILS__FOR_EACH_HELPER_2ARG(macro, arg1, arg2, a1, ...) \
  macro(arg1, arg2, a1) \
  __VA_OPT__(__DETAILS__FOR_EACH_AGAIN_2ARG __DETAILS__PARENS (macro, arg1, arg2, __VA_ARGS__))
#define __DETAILS__FOR_EACH_AGAIN_2ARG() __DETAILS__FOR_EACH_HELPER_2ARG

#define __DETAILS__FOR_EACH_HELPER_3ARG(macro, arg1, arg2, arg3, a1, ...) \
  macro(arg1, arg2, arg3, a1) \
  __VA_OPT__(__DETAILS__FOR_EACH_AGAIN_3ARG __DETAILS__PARENS (macro, arg1, arg2, arg3, __VA_ARGS__))
#define __DETAILS__FOR_EACH_AGAIN_3ARG() __DETAILS__FOR_EACH_HELPER_3ARG

#define __DETAILS__FOR_EACH_HELPER_4ARG(macro, arg1, arg2, arg3, arg4, a1, ...) \
  macro(arg1, arg2, arg3, arg4, a1) \
  __VA_OPT__(__DETAILS__FOR_EACH_AGAIN_4ARG __DETAILS__PARENS (macro, arg1, arg2, arg3, arg4, __VA_ARGS__))
#define __DETAILS__FOR_EACH_AGAIN_4ARG() __DETAILS__FOR_EACH_HELPER_4ARG

/*********************************************
 * FOR_EACH applies a macro on each arguments
 *********************************************/

/// @brief Applies 'macro' on each arguments
#define FOR_EACH(macro, ...)  \
  __VA_OPT__(__DETAILS__EXPAND(__DETAILS__FOR_EACH_HELPER(macro, __VA_ARGS__)))

/// @brief Applies 'macro' on each arguments, invoking 'macro(arg, <ARG>)'
#define FOR_EACH_1ARG(macro, arg, ...) \
  __VA_OPT__(__DETAILS__EXPAND(__DETAILS__FOR_EACH_HELPER_1ARG(macro, arg, __VA_ARGS__)))

/// @brief Applies 'macro' on each arguments, invoking 'macro(arg1, arg2, arg3, <ARG>)'
#define FOR_EACH_3ARG(macro, arg1, arg2, arg3, ...) \
  __VA_OPT__(__DETAILS__EXPAND(__DETAILS__FOR_EACH_HELPER_3ARG(macro, arg1, arg2, arg3, __VA_ARGS__)))

/// @brief Applies 'macro' on each arguments, invoking 'macro(arg1, arg2, arg3, arg4, <ARG>)'
#define FOR_EACH_4ARG(macro, arg1, arg2, arg3, arg4, ...) \
  __VA_OPT__(__DETAILS__EXPAND(__DETAILS__FOR_EACH_HELPER_4ARG(macro, arg1, arg2, arg3, arg4, __VA_ARGS__)))

/// @brief Applies 'macro' on each arguments, invoking 'macro(arg1, arg2, <ARG>)'
#define FOR_EACH_2ARG(macro, arg1, arg2, ...) \
  __VA_OPT__(__DETAILS__EXPAND(__DETAILS__FOR_EACH_HELPER_2ARG(macro, arg1, arg2, __VA_ARGS__)))

#endif // !__HG_MACRO