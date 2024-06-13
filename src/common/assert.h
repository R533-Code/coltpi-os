#ifndef __HG_ASSERT
#define __HG_ASSERT

#include "common/macro.h"
#include "common/intrinsics.h"
 
#ifndef COLTPI_DEBUG
  /// @brief Check if all conditions evaluates to true, else tries
  ///        to breakpoint with information 'msg'.
  #define assert_true(msg, bool, ...) do {} while(0)
#else
  #define __ASSERT_TRUE_AND_EXPAND(arg) && arg
  #define assert_true(msg, bool, ...) do { \
    if (!(bool FOR_EACH(__ASSERT_TRUE_AND_EXPAND, __VA_ARGS__))) { \
      intrinsic_break_0xcfcf("Line " STRINGIZE(__LINE__)  ": " msg, __PRETTY_FUNCTION__); \
    } } while (0)
#endif

#endif // !__HG_ASSERT