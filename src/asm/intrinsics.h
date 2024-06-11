#ifndef __HG_INTRINSICS
#define __HG_INTRINSICS

#include "common/macro.h"

FORCE_INLINE
/// @brief Expands to a 'wfe' instruction.
/// This is usually used inside of busy spinlock loops, to
/// put the core in a low-power standby state.
/// This is usually paired with 'intrinsic_wakeall' in
/// the thread that acquire the spinlock.
void intrinsic_pause()
{
  asm ("wfe");
}

FORCE_INLINE
/// @brief Expands to a 'sev' instruction.
/// This is usually used after releasing a spinlock, to
/// wake the cores that are in low-power standby state.
/// This is usually paired with 'instrinsic_pause' in
/// the threads that acquire the spinlock.
void intrinsic_wakeall()
{
  asm ("sev");
}

#endif // !__HG_INTRINSICS