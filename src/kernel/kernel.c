#include <common/stdlib.h>
#include <common/stdio.h>
#include <common/dispatcher.h>

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
	malloc_init();
	dispatcher_init();
	printk("Hello world!\n");
	print_to_ascii("UphillOS");
	start_counter();

	return 0;
}

void exception_handler() {
	printk("Nope");
}
