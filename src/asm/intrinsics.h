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

/// @brief Expands to an invalid instruction
void intrinsic_und()
{
  asm volatile (".inst 0xe7f001f0");
}

#define __ASM_BLOCK(value) asm (value)
/// @brief Expands to a 'brk' instruction.
/// The macro is written in this clumsy way because
/// otherwise syntax highlighting acts weirdly.
#define intrinsic_break(u16) __ASM_BLOCK("brk" "#" STRINGIZE(u16))

NEVER_INLINE
/// @brief Expands to intrinsic_break(0xcfcf)
/// This function is specifically called for 
/// assertion failures in the kernel, as gdb
/// will insert a breakpoint for this function.
void intrinsic_break_0xcfcf(const char msg[], const char fn[])
{
  intrinsic_break(0xcfcf);
}

#endif // !__HG_INTRINSICS