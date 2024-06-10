#include "constants.h"
.arch armv8.2-a
.section ".text.boot"
.globl _start

.extern memset

_start:
  mrs     x0, mpidr_el1        
  and     x0, x0, #0xFF  // Check processor id
  cbz     x0, _main       // Hang for all non-primary CPU
_proc_hang:
  wfe
  b       _proc_hang

_main:
  // Call memset to zero out the .bss section
  ldr     x0, __clt_bss_start
  mov     x1, xzr
  ldr     x2, __clt_bss_end
  sub     x2, x2, x0
  bl      memset
  
  mov     sp, #LOW_MEMORY
  bl      kernel_main
  b       _proc_hang