#include "common/typedef.h"
#include "boot/constants.h"
#include "common/memop.h"
#include "atomic/atomic_int.h"
#include "common/assert.h"

/// @brief The first function called by the bootloader
void kernel_main()
{
  hw_random_t a = intrinsic_rand(); 
  return;
}