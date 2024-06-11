#ifndef __HG_ATOMIC_FENCE
#define __HG_ATOMIC_FENCE

#include "common/macro.h"

/// @brief The memory ordering used by atomic instructions
/// For more information, see:
/// `https://en.cppreference.com/w/cpp/atomic/memory_order`
typedef enum
{
  /// @brief Relaxed operation.
  /// There are no synchronization or ordering constraints imposed on other
  /// reads or writes, only this operation's atomicity is guaranteed.
  ORDER_RELAXED = __ATOMIC_RELAXED,
  /// @brief Acquire operation.
  /// A load operation with this memory order performs the acquire operation:
  /// no reads or writes in the current thread can be reordered before this load.
  /// All writes in other threads that release the same atomic variable are
  /// visible in the current thread.
  ORDER_ACQUIRE = __ATOMIC_ACQUIRE,
  /// @brief Release operation.
  /// A store operation with this memory order performs the release operation:
  /// no reads or writes in the current thread can be reordered after this store.
  /// All writes in the current thread are visible in other threads that acquire
  /// the same atomic variable.
  ORDER_RELEASE = __ATOMIC_RELEASE,
  /// @brief Acquire-Release operation.
  /// A read-modify-write operation with this memory order is both an acquire
  /// operation and a release operation.
  /// No memory reads or writes in the current thread can be reordered before
  /// the load, nor after the store.
  /// All writes in other threads that release the same atomic variable are visible
  /// before the modification and the modification is visible in other threads that
  /// acquire the same atomic variable.
  ORDER_ACQ_REL = __ATOMIC_ACQ_REL,
  /// @brief Sequential Consistency operation.
  /// A load operation with this memory order performs an acquire operation,
  /// a store performs a release operation, and read-modify-write performs
  /// both an acquire operation and a release operation, plus a single total
  /// order exists in which all threads observe all modifications
  /// in the same order.
  ORDER_SEQ_CST = __ATOMIC_SEQ_CST
} MemoryOrdering;

FORCE_INLINE
/// @brief This function acts as a hardware synchronization fence between
///        threads.
/// @param order The MemoryOrdering (all are valid)
void atomic_thread_fence(MemoryOrdering order)
{
  __atomic_thread_fence(order);
}

FORCE_INLINE
/// @brief This function acts as a compiler synchronization fence between a
///        thread and signal handlers based in the same thread.
/// For more information, see:
/// `https://stackoverflow.com/questions/14581090/how-to-correctly-use-stdatomic-signal-fence`
/// @param order The MemoryOrdering (all are valid)
void atomic_signal_fence(MemoryOrdering order)
{
  __atomic_signal_fence(order);
}

#endif // !__HG_ATOMIC_FENCE