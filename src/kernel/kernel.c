
#define UART16550BASE 0xb80003f8

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

int main(void) {
	printk("Hello world!\n");

	return 0;
}
