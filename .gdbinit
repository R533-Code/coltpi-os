target remote localhost:1234
add-symbol-file build/kernel8.elf
set pagination off
break kernel_main
layout split