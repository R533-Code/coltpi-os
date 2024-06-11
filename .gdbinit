target remote localhost:1234
add-symbol-file build/debug/kernel8.elf
set pagination off
break kernel_main
break intrinsic_break_0xcfcf
layout split