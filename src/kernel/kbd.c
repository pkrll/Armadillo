

#include <common/stdint.h>
#include <kernel/kbd.h>

extern char _read_kbd_asm();

__attribute__((unused))static char* scancode __attribute__((section(".data")));


char getchar();
char getScancode();
static inline char read_kbd();
/*
* @brief  Enables the keyboard by writing 0xae to port adress 0x64
*
*/
void kbd_init() {
  //char __attribute__ ((unused))bajs;
  //bajs = read_kbd();
}

/*
PS/2 keyboard code.
Dependencies:
inb function and scancode table.
*/
char getScancode() {
    char c=0;
    do {
        if(read_kbd()!=c) {
            c=read_kbd();
            if(c>0)
                return c;
        }
    } while(1);
}

char getchar() {
    return scancode[getScancode()+1];
}

/*
* @brief  Receives an 8-bit value from the keyboard data port.
*/
static inline char read_kbd()
{
  return _read_kbd_asm();
}
