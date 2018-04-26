#include <common/pcb.h>
#include <common/malloc.h>
#include <common/list.h>
#include <mips/pcb_offsets.h>
#include <common/dispatcher.h>

static list_t *ready_queue __attribute__((section(".bss")));
extern pcb_t *running_process __attribute__((section(".bss")));

void process_2(){
	//printk("2");
	for (int i = 1; i < 10000000; i++);
  asm volatile("syscall");
}

void process_1(){
	//printk("1");
	for (int i = 1; i < 10000000; i++);
  asm volatile("syscall");
}

void process_0(){
	//sprintk("0");
	for (int i = 1; i < 10000000; i++);
  asm volatile("syscall");
}

void init_processes(){
  pcb_t *p0 = init_pcb(0, &process_0);
  pcb_t *p1 = init_pcb(1, &process_1);
  pcb_t *p2 = init_pcb(2, &process_2);
  enqueue(ready_queue, p1);
  enqueue(ready_queue, p2);
  running_process = p0;
}

void dispatcher_init(){
  process_mem_space = malloc(5*PCB_SIZE);
  ready_queue = list_new();
  init_processes(process_mem_space);
}



void process_switch(){
  enqueue(ready_queue, running_process);
  pcb_t *next = pop(ready_queue);
  set_pcb_state(next, running);
  running_process = next;
}
