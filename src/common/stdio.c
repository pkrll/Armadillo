#include <common/stdio.h>

void putchar(char c) {
	// Line status register.
	volatile int* lsr = (volatile int*)(UART16550BASE + 0x0028);
	// Transmitter holding register.
	volatile int* thr = (volatile int*)(UART16550BASE);

	// Wait until THR is empty.
	while(((*lsr) & 0x20) == 0) { }
	*thr = c;
}

void printk(const char* s) {
	while(*s) {
		putchar(*s);
		s++;
	}
}

void print_to_ascii(const char *string) {
	char *asciipos = (char *) ASDCIIDISPLAY;
	for (int i = 0; i < 8; i++) {
		asciipos[i * 8] = string[i];
	}
}

void reset_led() {
	char *led = (char *) LEDDISPLAY;
	*led = 0b0;
}

void print_to_led(const int position) {
	char *led = (char *) LEDDISPLAY;
	*led = 0b00000001 << (position - 1) | led[0];
}
