#include <common/stdlib.h>
#include <common/stdio.h>
#include <common/dispatcher.h>
#include <common/processes.h>

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
void addrl_handler() {
	delay();
	printk("Addrl exception! (Cause 4) Load from illegal address exception\n");
}

void addrs_handler() {
	delay();
	printk("Addrs exception! (Cause 5) Store to illegal address exception\n");
}

void ibus_handler() {
	delay();
	printk("Ibus exception! (Cause 6) Bus error on instruction fetch\n");
}

void dbus_handler() {
	delay();
	printk("Dbus exception! (Cause 7) Bus error on data reference\n");
}

void bkpt_handler() {
	delay();
	printk("Bkpt exception! (Cause 9) Break instruction executed\n");
}

void ri_handler() {
	delay();
	printk("Ri exception! (Cause 10) Reserved instruction\n");
}

void ovf_handler() {
	delay();
	printk("Ovf exception! (Cause 12) Arithmetic overflow\n");
}

void unkown_exception() {
	delay();
	//print the cause with %d
	printk("Unknown exception with cause ___\n");
}

void unhandled_interrupt() {
	delay();
	printk("Unhandled interrupt\n");
}

void interupt_handler() {
	//delay();
	printk("\n -- Timer Interupt, switching process \n");
	// spawn_process(process_1);
	//asm volatile("syscall");
}
