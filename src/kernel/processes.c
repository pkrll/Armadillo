#include <common/processes.h>
#include <common/stdlib.h>
#include <common/dispatcher.h>

void process_5(){
	while (1) {
		for (int i = 1; i < 10000000; i++);
		printk("5");
		asm volatile("syscall");
	}
}

void process_4(){
	while (1) {
		for (int i = 1; i < 10000000; i++);
		printk("4");
		asm volatile("syscall");
	}
}

void process_3(){
	while (1) {
		for (int i = 1; i < 10000000; i++);
		printk("3");
		asm volatile("syscall");
	}
}

/*
*	Workspace for process 2
*/
void process_2(){
	while (1) {
		for (int i = 1; i < 5000000; i++);
		printk("2");
		asm volatile("syscall");
	}
}

/*
*	Workspace for process 1
*/
void process_1(){
	while (1) {
		for (int i = 1; i < 50000000; i++);
		printk("#Initializing process 1, counting up to 5...\n");
    //for (int i = 1; i < 100000000; i++);
    // printk("1 ");
    //for (int i = 1; i < 100000000; i++);
    // printk("2 ");
    //for (int i = 1; i < 100000000; i++);
    // printk("3 ");
    //for (int i = 1; i < 100000000; i++);
    // printk("error... ");
    //for (int i = 1; i < 100000000; i++);

    //asm volatile("syscall");
	}
}

/*
*	Workspace for process 0
*/
void process_0(){
	while (1) {
		for (int i = 1; i < 50000000; i++);
		printk("#Initializes process 0, calculating 1 + 1...");
  	for (int i = 1; i < 50000000; i++);
    printk(" = 2 \n");
		//spawn_process(process_1);
		//asm volatile("syscall");
	}
}
