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
    .global __clt_bss_start // void*
    // The Block Starting Symbol end, defined by the linker
    .global __clt_bss_end   // void*

    // The Read Only Data start, defined by the linker
    .global __clt_rodata_start // void*
    // The Read Only Data end, defined by the linker
    .global __clt_rodata_end   // void*

    // The Text start, defined by the linker
    .global __clt_text_start // void*
    // The Text end, defined by the linker
    .global __clt_text_end   // void*
#else
    #include "common/typedef.h"
    /// @brief LINKER DECLARATION FLAG
    /// @warning Do not use! Use clt_bss_start instead.
    extern char __clt_bss_start[];
    /// @brief Pointer to the start of the .bss section (aligned to 16 byte boundary)
    static const byte* const clt_bss_start = (const byte* const)&__clt_bss_start;
    /// @brief LINKER DECLARATION FLAG
    /// @warning Do not use! Use clt_bss_end instead.
    extern char __clt_bss_end[];
    /// @brief Pointer to the end of the .bss section
    static const byte* const clt_bss_end = (const byte* const)&__clt_bss_end;
    
    /// @brief LINKER DECLARATION FLAG
    /// @warning Do not use! Use clt_rodata_start instead.
    extern char __clt_rodata_start[];
    /// @brief Pointer to the start of the .rodata section (aligned to 16 byte boundary)
    static const byte* const clt_rodata_start = (const byte* const)&__clt_rodata_start;
    /// @brief LINKER DECLARATION FLAG
    /// @warning Do not use! Use clt_rodata_end instead.
    extern char __clt_rodata_end[];
    /// @brief Pointer to the end of the .rodata section
    static const byte* const clt_rodata_end = (const byte* const)&__clt_rodata_end;
    
    /// @brief LINKER DECLARATION FLAG
    /// @warning Do not use! Use clt_text_start instead.
    extern char __clt_text_start[];
    /// @brief Pointer to the start of the .text section (aligned to 16 byte boundary)
    static const byte* const clt_text_start = (const byte* const)&__clt_text_start;
    /// @brief LINKER DECLARATION FLAG
    /// @warning Do not use! Use clt_text_end instead.
    extern char __clt_text_end[];
    /// @brief Pointer to the end of the .text section
    static const byte* const clt_text_end = (const byte* const)&__clt_text_end;
#endif // !__ASSEMBLER__

#endif // !HG_CONSTANTS