target remote localhost:1234
add-symbol-file build/kernel8.elf
layout split
set pagination off
break kernel_main