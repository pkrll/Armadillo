ENTRY(start)
OUTPUT_FORMAT(elf32-littlemips)

SECTIONS
{
    _ram = 0x80000000;

    . = 0x80100000;
    __start = .;
    __text_start = .;

    .text :
    {
        KEEP(*(.ktext))
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    __text_end = .;

    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096); /* align to page size */
    __rodata_end = .;

    __data_start = .;
    .data :
    {
        *(.data)
    }

    . = ALIGN(4096); /* align to page size */
    __data_end = .;

    __bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }

    . = ALIGN(4096); /* align to page size */
    __bss_end = .;
    __end = .;
}
