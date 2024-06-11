#ifndef __HG_ATOMIC_FLAG
#define __HG_ATOMIC_FLAG

#include "common/typedef.h"
#include "atomic_fence.h"

/// @brief Represents an atomic flag
typedef struct
{
  /// @brief The internal flag
  /// @warning Do not use this member! Make use of the atomic_flag_* functions.
  bool _flag;
} atomic_flag;


FORCE_INLINE
/// @brief Initializes the flag to a cleared state
/// @param flag The flag to initialize
/// @warning This does not do any synchronization
void atomic_flag_init(mutptr(atomic_flag) flag)
{
  flag->_flag = 0;
}

NO_DISCARD FORCE_INLINE
/// @brief Performs an atomic test and set on the flag.
/// @param flag The flag on which to perform the test and set
/// @param order The MemoryOrdering (all are valid)
/// @return True if the previous state was set
bool atomic_flag_test_and_set(mutptr(atomic_flag) flag, MemoryOrdering order)
{
  return __atomic_test_and_set((volatile void*)&flag->_flag, order);
}

FORCE_INLINE
/// @brief Atomically clears the flag.
/// @param flag The flag on which to perform the clear
/// @param order The MemoryOrdering (RELAXED, SEQ_CST, RELEASE)
void atomic_flag_clear(mutptr(atomic_flag) flag, MemoryOrdering order)
{
  __atomic_clear(&flag->_flag, order);
}

NO_DISCARD FORCE_INLINE
/// @brief Atomically get the state of the flag.
/// @param flag The flag on which to perform the load
/// @param order The MemoryOrdering (RELAXED, SEQ_CST, ACQUIRE)
/// @return True if the flag was set when the load was performed
bool atomic_flag_test(ptr(atomic_flag) flag, MemoryOrdering order)
{
  return __atomic_load_n(&flag->_flag, order) != 0;
}

#endif //!__HG_ATOMIC_FLAG