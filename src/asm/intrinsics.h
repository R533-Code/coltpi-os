#ifndef HG_INSTRINSICS
#define HG_INSTRINSICS

#include "common/macro.h"

FORCE_INLINE
/// @brief Expands to a 'wfe' instruction.
void intrinsic_pause()
{
  asm ("wfe");
}

#endif // !HG_INSTRINSICS