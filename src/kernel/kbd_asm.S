#include <mips/registers.h>
#include <mips/adresses.h>

.globl _read_kbd_asm

.section .text

_read_kbd_asm:
  li T0, KBD_DATA_PORT # Load adress to data port
  lb V0, 0(T0)        # First byte of port adress 
  jr RA
  nop
