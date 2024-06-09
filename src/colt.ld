SECTIONS
{
    /* The address at which the kernel is loaded */
    __clt_kernel_load_address = .;

    /* Code section */
    .text : {
        __clt_text_start = .;
        KEEP(*(.text.boot)) *(.text);
        __clt_text_end   = .;
        /* The size of the .text section */
        __clt_text_size = (__clt_text_end - __clt_text_start);
    }

    /* Read-only section */
    .rodata : {
        . = ALIGN(16); /* Aligned at a 16 byte boundary */
        __clt_rodata_start = .;
        *(.rodata);
        __clt_rodata_end = .;
        /* The size of the .rodata section */
        __clt_rodata_size = (__clt_rodata_end - __clt_rodata_start);
    }

    /* Block Starting Symbol section */
    .bss (NOLOAD) : {
        . = ALIGN(16); /* Aligned at a 16 byte boundary */
        __clt_bss_start = .;
        *(.bss);
        __clt_bss_end = .;
        
        /* The size of the .bss section */
        __clt_bss_size = (__clt_bss_end - __clt_bss_start);
    }

    /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}