#ifndef __HG_SPINLOCK
#define __HG_SPINLOCK

#include "atomic/atomic_flag.h"
#include "asm/intrinsics.h"

/// @brief Represents a spinlock.
/// A spinlock is the simplest mutex:
/// When a thread locks the mutex, all other threads
/// that try to acquire the lock keep spinning till
/// the lock can be acquired again.
/// This implementation still does the spinning in
/// the most appropriate way, by using `intrinsic_pause`
/// and `intrinsic_wakeall`.
typedef struct
{
  atomic_flag _flag;
} spinlock;

FORCE_INLINE
/// @brief Initializes the lock to a non-owned state
/// @param lock The lock to initialize
void spinlock_init(mutptr(spinlock) lock)
{
  atomic_flag_init(&lock->_flag);
}

/// @brief Locks the mutex.
/// If another thread already owns the mutex, then
/// this thread will spin till the mutex is released.
/// @param lock The lock to acquire
void spinlock_lock(mutptr(spinlock) lock)
{
  while (atomic_flag_test_and_set(&lock->_flag, ORDER_RELAXED))
    while (atomic_flag_test(&lock->_flag, ORDER_RELAXED))
      intrinsic_pause();      
  atomic_thread_fence(ORDER_ACQUIRE);  
}

FORCE_INLINE NO_DISCARD
/// @brief Tries to lock the mutex.
/// This method returns immediatly and does not block the thread.
/// @param lock The lock to try to acquire
/// @return True if the current thread acquired the mutex, false
///         if the mutex was already locked.
bool spinlock_try_lock(mutptr(spinlock) lock)
{
  return !atomic_flag_test_and_set(&lock->_flag, ORDER_ACQUIRE);
}

FORCE_INLINE
/// @brief Unlocks the mutex
/// @param lock The mutex to release
void spinlock_unlock(mutptr(spinlock) lock)
{
  atomic_flag_clear(&lock->_flag, ORDER_RELEASE);
  intrinsic_wakeall();
}

#endif // !__HG_SPINLOCK