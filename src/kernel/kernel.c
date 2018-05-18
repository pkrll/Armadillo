#include <common/stdlib.h>
#include <common/stdio.h>
#include <kernel/dispatcher.h>
#include <kernel/exceptions.h>
#include <common/processes.h>

extern int context_switch();

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
	mem_init();
	dispatcher_init();
	process_1();
	printk("Hello world!\n");
	print_to_ascii("UphillOS");
	start_counter();
	return 0;
}

/*-------------------Exception handlers--------------------*/

void exception_handler(int cause) {
	delay();
	printf("EXCEPTION CAUGHT: %s\n", exceptions[cause]);
}

void unhandled_interrupt() {
	delay();
	printk("Unhandled interrupt\n");
}

void interrupt_handler() {
	int pid = get_pid(get_current_pcb());
	printf("\n -- Timer Interrupt, switching from process %d \n", pid);
}
