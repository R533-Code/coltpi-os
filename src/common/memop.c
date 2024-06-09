#include "memop.h"

#define MEMCPY_USING_(type) \
do { \
  const size_t div = sizeof(type); \
  while ((uintptr)src % div != 0) { \
    *dest_b++ = *src_b++; \
    count--; \
  } \
  size_t qword_count = count / div; \
  size_t byte_count = count % div; \
  while (qword_count != 0) \
  { \
    *(mutptr(type))dest_b = *(ptr(type))src_b; \
    dest_b += div; \
    src_b += div; \
    --qword_count; \
  } \
  while (byte_count != 0) \
  { \
    *dest_b++ = *src_b++; \
    --byte_count; \
  } \
} while (0)

void memcpy(opaque_mutptr dest, opaque_ptr src, size_t count)
{
  mutptr(byte) dest_b = (mutptr(byte))dest;
  ptr(byte) src_b = (ptr(byte))src;

  if ((uintptr)dest % sizeof(u64) == (uintptr)src % sizeof(u64))
    MEMCPY_USING_(u64);
  else if ((uintptr)dest % sizeof(u32) == (uintptr)src % sizeof(u32))
    MEMCPY_USING_(u32);
  else if ((uintptr)dest % sizeof(u16) == (uintptr)src % sizeof(u16))
    MEMCPY_USING_(u16);
  else
  {
    // Copy byte by bytes
    while (count != 0)
    {
      *dest_b++ = *src_b++;
      count--;
    }
  }    
}

#undef MEMCPY_USING_

void memset(opaque_mutptr dest, byte value, size_t count)
{
  mutptr(byte) dest_b = (mutptr(byte))dest;
  
  while ((uintptr)dest_b % 8 != 0)
  {
    *dest_b = value;
    dest_b++;
    count--;
  }
  
  size_t qword_count = count / 8;
  size_t byte_count = count % 8;

  const u32 VALUEx4 = (value) | (value << 8) | (value << 16) | (value << 24);
  const u64 VALUEx8 = (VALUEx4) | (VALUEx4 << 32);
  while (qword_count != 0)
  {
    *(mutptr(u64))dest_b = VALUEx8;
    dest_b += 8;
    --qword_count;
  }
  while (byte_count != 0)
  {
    *dest_b++ = value;
    --byte_count;
  }
}
