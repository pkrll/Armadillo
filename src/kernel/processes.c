#include <common/processes.h>
#include <common/stdlib.h>
#include <kernel/dispatcher.h>
#include <common/k_rand.h>
#include <kernel/pcb.h>

#define wait(x) for (int _i = 0; _i < x; _i++);

void exit() {
	asm volatile ("li $a0, 99");
	asm volatile ("syscall");
}

void delay() {
	for (int i = 1; i < 100000000; i++);
}

void process_6() {
	while (1) {
		delay();
		printk("6");
		asm volatile("syscall");
	}
}

void process_5() {
	while (1) {
		delay();
		printk("5");
		asm volatile("syscall");
	}
}

void process_4() {
	while (1) {
		delay();
		printk("4");
		asm volatile("syscall");
	}
}

/*
*	Workspace for process 3
*/
void process_3() {
	while (1) {
		for (int i = 1; i < 100000000; i++); //delay();
		printk("PROCESS_3\n");
	}
}

/*
*	Workspace for process 2
*/
void process_2() {
	while (1) {
		for (int i = 1; i < 100000000; i++); //delay();
		printk("Process 2 counting up to 5...\n");
		for (int i = 1; i < 100000000; i++); //delay();
		printk("1\n");
		for (int i = 1; i < 100000000; i++); //delay();
		printk("2\n");
		for (int i = 1; i < 100000000; i++); //delay();
		printk("3\n");
		for (int i = 1; i < 100000000; i++); //delay();
		printk("error...\n");
		//asm volatile("syscall");
	}
}

/*
*	Workspace for process 1
*/
void process_1() {
	for (int i = 0; i < 10; i++) {
		int random = rand(100000000);
		for (int i = 0; i < random; i++); //delay
		printk("Doing something\n");
	}
	asm volatile ("li $a0, 99");
	asm volatile ("syscall");
}

void fibonacci() {
	int n = 47; // More than that we get overflow...
	unsigned long f1 = 0;
	unsigned long f2 = 1;
	unsigned long next = 0;

	printf("\n==================\nPrinting the first %d terms of the Fibonacci series...\n==================\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d, ", f1);
		next = f1 + f2;
		f1 = f2;
		f2 = next;

		int random = rand(100000000);
		wait(random);
	}

	printf("\n==================\nDone printing the fibonacci series\n==================\n\n");
	exit();
}

void square_numbers() {
	int n = 1000;
	int x = 0;
	int s = 1;
	printf("\n==================\nPrinting the square numbers\n==================\n");
	for (int i = 0; i < n; i++, x = 2 * i + 1) {
		s = s + x;
		printf("%d ", s);

		int random = rand(50000000);
		wait(random);
	}

	printf("\n==================\nDone printing the square numbers\n==================\n\n");
	exit();
}

void triangle_numbers() {
	int n = 10;
	int last = 1;
	printf("\n==================\nPrinting the triangle numbers\n==================\n\n");
	for (int i = 0; i < n; i++) {
		last = last + i;
		printf("%d ", i + last);

		int random = rand(50000000);
		wait(random);
	}

	printf("\n==================\nDone printing the triangle numbers\n==================\n\n");

	exit();
}
