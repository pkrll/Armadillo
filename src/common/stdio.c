#include <common/stdio.h>
#include <common/stdlib.h>
#include <stdarg.h>

// -------------------------------
// Declarations
// -------------------------------

/**
 * Converts and prints the next argument in args depending
 * on the format specifier.
 *
 * @param specifier A format specifier.
 * @param args      The list of arguments.
 */
void convert(char specifier, va_list *args);
/**
 * Stores a character in the UART16550BASE register,
 * effectively writing out a char to the screen.
 *
 * @param c The character to print.
 */
void putchar(char character);

// -------------------------------
// Public functions
// -------------------------------

void printk(const char* string) {
	while(*string) {
		putchar(*string);
		string++;
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

// -------------------------------
// Internal functions
// -------------------------------

void putchar(char character) {
	// Line status register.
	volatile int *lsr = (volatile int*)(UART16550BASE + 0x0028);
	// Transmitter holding register.
	volatile int *thr = (volatile int*)(UART16550BASE);

	// Wait until THR is empty.
	while(((*lsr) & 0x20) == 0) { }
	*thr = character;
}

void convert(char specifier, va_list *args) {
	char *arg;

	switch (specifier) {
	case 'd':
		arg = number_to_char(va_arg(*args, int));
		break;
	case 'h':
		arg = hexadecimal_to_char(va_arg(*args, unsigned int));
		break;
	case 's':
		arg = va_arg(*args, char *);
		break;
	}

	printk(arg);
}
