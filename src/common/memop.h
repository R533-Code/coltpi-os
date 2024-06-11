#ifndef __HG_MEMOP
#define __HG_MEMOP

#include "common/typedef.h"
#include "common/macro.h"

/// @brief Copies 'count' bytes from 'src' to 'dest'
/// @warning 'src' and 'dest' must not overlap.
/// @param dest The destination bytes
/// @param src The source bytes
/// @param count The count of bytes
void memcpy(opaque_mutptr RESTRICT dest, opaque_ptr RESTRICT src, size_t count);

/// @brief Sets 'count' bytes in 'dest' to 'value'
/// @param dest The destination bytes
/// @param value The value to set the bytes to
/// @param count The count of bytes
void memset(opaque_mutptr dest, byte value, size_t count);

#endif // !__HG_MEMOP