
#define UART16550BASE 0xb80003f8
#define DISPLAYREGIST 0x1F000400

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

void print_to_led(const char *string) {
	char *asciipos = (char *) DISPLAYREGIST + 0x00000018;

	for (int i = 0; i < 8; i++) {
		asciipos[i * 8] = string[i];
	}
}

int main(void) {
	// printk("Hello world!\n");
	print_to_led("Hello World, this is foo");

	return 0;
}
