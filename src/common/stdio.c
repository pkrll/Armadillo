#include <common/stdio.h>
#include <stdarg.h>

void convert(char specifier, va_list *args);
void putchar(char c);

void printk(const char* s) {
	while(*s) {
		putchar(*s);
		s++;
	}
}

void printf(const char *string, ...) {
	va_list args;
	va_start(args, string);

	while (*string) {
		while (*string != '%') {
			putchar(*string);
			string++;
			if (*string == '\0') return;
		}

		string++;
		convert(*string++, &args);
	}

	va_end(args);
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

void putchar(char c) {
	// Line status register.
	volatile int* lsr = (volatile int*)(UART16550BASE + 0x0028);
	// Transmitter holding register.
	volatile int* thr = (volatile int*)(UART16550BASE);

	// Wait until THR is empty.
	while(((*lsr) & 0x20) == 0) { }
	*thr = c;
}

void convert(char specifier, va_list *args) {
	switch (specifier) {
		case 'd':
			break;
		case 's':
			printk(va_arg(*args, char *));
			break;
	}
}
