#include <common/memory.h>

#define UART16550BASE 0xb80003f8
#define DISPLAYREGIST 0xbf000400 // Boot mode: 0x1F000400 ?
#define ASDCIIDISPLAY	DISPLAYREGIST + 0x00000018
#define LEDDISPLAY 		DISPLAYREGIST + 0x00000008

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

void start_counter() {
	while (1) {
		for (int i = 1; i < 10; i++) {
			for (int i = 0; i < 100000000; i++) { /* Pause... */ }

			if (i == 9) {
				asm volatile("li $a0, 0x1;" "syscall");
			} else {
				print_to_led(i);
			}

		}
	}
}

int main(void) {
	// printk("Hello world!\n");
	// print_to_ascii("UphillOS");
	// start_counter();
	mem_init();
	char *array = malloc(sizeof(char)*3);
	array[0] = 'a';
	array[1] = '\n';
	array[2] = '\0';
	printk(array);

	char *array2 = malloc(sizeof(char)*3);
	array2[0] = 'd';
	array2[1] = '\n';
	array2[2] = '\0';
	printk(array2);
	printk(array);

	return 0;
}

void exception_handler() {
	printk("Nope");
}
