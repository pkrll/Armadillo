#include <mips/registers.h>

.globl _read_kbd_asm

.section .data
  KBD_DATA_PORT: .word 0x60

.section .text

_read_kbd_asm:
  li $t0, KBD_DATA_PORT
  lb $v0, 0($t0)
  jr $ra
