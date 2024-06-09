#ifndef HG_CONSTANTS
#define HG_CONSTANTS

#define PAGE_SHIFT	 		    12
#define TABLE_SHIFT 			9
#define SECTION_SHIFT			(PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE   			(1 << PAGE_SHIFT)	
#define SECTION_SIZE			(1 << SECTION_SHIFT)	

#define LOW_MEMORY              (2 * SECTION_SIZE)

#ifdef __ASSEMBLER__
    // The Block Starting Symbol start, defined by the linker
    .extern __clt_bss_start // void*
    // The Block Starting Symbol end, defined by the linker
    .extern __clt_bss_end   // void*
    // The Block Starting Symbol size, defined by the linker
    .extern __clt_bss_size  // u32

    // The Read Only Data start, defined by the linker
    .extern __clt_rodata_start // void*
    // The Read Only Data end, defined by the linker
    .extern __clt_rodata_end   // void*
    // The Read Only Data size, defined by the linker
    .extern __clt_rodata_size  // u32

    // The Text start, defined by the linker
    .extern __clt_text_start // void*
    // The Text end, defined by the linker
    .extern __clt_text_end   // void*
    // The Text size, defined by the linker
    .extern __clt_text_size  // u32
#else
    #include "common/typedef.h"
    
    /// @brief Pointer to the start of the .bss section (aligned to 16 byte boundary)
    extern byte* __clt_bss_start;
    /// @brief Pointer to the end of the .bss section
    extern byte* __clt_bss_end;
    /// @brief Pointer to the start of the .rodata section (aligned to 16 byte boundary)
    extern byte* __clt_rodata_start;
    /// @brief Pointer to the end of the .rodata section
    extern byte* __clt_rodata_end;
    /// @brief Pointer to the start of the .text section (aligned to 16 byte boundary)
    extern byte* __clt_text_start;
    /// @brief Pointer to the end of the .text section
    extern byte* __clt_text_end;

    /// @brief The size of the .bss section
    extern const u32 __clt_bss_size;
    /// @brief The size of the .rodata section
    extern const u32 __clt_rodata_size;
    /// @brief The size of the .text section
    extern const u32 __clt_text_size;
#endif // !__ASSEMBLER__

#endif // !HG_CONSTANTS