#ifndef HG_ATOMIC_INT
#define HG_ATOMIC_INT

#include "atomic/atomic_fence.h"
#include "common/typedef.h"

#define CREATE_ATOMIC_INT(ty) \
typedef struct \
{ \
  ty _flag; \
} CONCAT(atomic_, ty); \
FORCE_INLINE \
void CONCAT3(atomic_, ty, _init)(mutptr(CONCAT(atomic_, ty)) ptr) \
{ \
  ptr->_flag = 0; \
} \
FORCE_INLINE NO_DISCARD \
ty CONCAT3(atomic_, ty, _load)(mutptr(CONCAT(atomic_, ty)) ptr, MemoryOrdering order) \
{ \
  return __atomic_load_n(&ptr->_flag, order); \
} \
FORCE_INLINE \
void CONCAT3(atomic_, ty, _store)(mutptr(CONCAT(atomic_, ty)) ptr, ty value, MemoryOrdering order) \
{ \
  __atomic_store_n(&ptr->_flag, value, order); \
} \
FORCE_INLINE NO_DISCARD \
ty CONCAT3(atomic_, ty, _exchange)(mutptr(CONCAT(atomic_, ty)) ptr, ty value, MemoryOrdering order) \
{ \
  return __atomic_exchange_n(&ptr->_flag, value, order); \
} \
FORCE_INLINE NO_DISCARD \
ty CONCAT3(atomic_, ty, _fetch_add)(mutptr(CONCAT(atomic_, ty)) ptr, ty value, MemoryOrdering order) \
{ \
  return __atomic_fetch_add(&ptr->_flag, value, order); \
} \
FORCE_INLINE NO_DISCARD \
ty CONCAT3(atomic_, ty, _fetch_sub)(mutptr(CONCAT(atomic_, ty)) ptr, ty value, MemoryOrdering order) \
{ \
  return __atomic_fetch_sub(&ptr->_flag, value, order); \
} \
FORCE_INLINE NO_DISCARD \
ty CONCAT3(atomic_, ty, _fetch_and)(mutptr(CONCAT(atomic_, ty)) ptr, ty value, MemoryOrdering order) \
{ \
  return __atomic_fetch_and(&ptr->_flag, value, order); \
} \
FORCE_INLINE NO_DISCARD \
ty CONCAT3(atomic_, ty, _fetch_xor)(mutptr(CONCAT(atomic_, ty)) ptr, ty value, MemoryOrdering order) \
{ \
  return __atomic_fetch_xor(&ptr->_flag, value, order); \
} \
FORCE_INLINE NO_DISCARD \
ty CONCAT3(atomic_, ty, _fetch_or)(mutptr(CONCAT(atomic_, ty)) ptr, ty value, MemoryOrdering order) \
{ \
  return __atomic_fetch_or(&ptr->_flag, value, order); \
} \
FORCE_INLINE NO_DISCARD \
bool CONCAT3(atomic_, ty, _compare_exchange_weak)(mutptr(CONCAT(atomic_, ty)) ptr, mutptr(ty) expected, ty desired, MemoryOrdering success, MemoryOrdering failure) \
{ \
  return __atomic_compare_exchange_n(&ptr->_flag, expected, desired, true, success, failure); \
} \
FORCE_INLINE NO_DISCARD \
bool CONCAT3(atomic_, ty, _compare_exchange_strong)(mutptr(CONCAT(atomic_, ty)) ptr, mutptr(ty) expected, ty desired, MemoryOrdering success, MemoryOrdering failure) \
{ \
  return __atomic_compare_exchange_n(&ptr->_flag, expected, desired, false, success, failure); \
} \

CREATE_ATOMIC_INT(u8);
CREATE_ATOMIC_INT(u16);
CREATE_ATOMIC_INT(u32);
CREATE_ATOMIC_INT(u64);
CREATE_ATOMIC_INT(i8);
CREATE_ATOMIC_INT(i16);
CREATE_ATOMIC_INT(i32);
CREATE_ATOMIC_INT(i64);

#endif // !HG_ATOMIC_INT