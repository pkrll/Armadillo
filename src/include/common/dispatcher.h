#ifndef __DISPATCHER_H_
#define __DISPATCHER_H_

#include <common/stdlib.h>
#include <common/stdio.h>
#include <common/pcb.h>
#include <common/memory.h>
#include <common/queue.h>

//__attribute__((unused))static addr_t process_mem_space __attribute__((section(".bss")));

/*
*	@brief	Allocates the ready queue and initializes all processes
*/
void dispatcher_init();

/*
*	@brief	Enqueues the running process into the ready queue, pops another process
*					from the queue and assigns it as the running process.
*/
void process_switch();

/*
*	@brief	Returns the adress for the PCB of the currently running process
*
* @return Adress of the current process' PCB
*/
pcb_t *get_current_pcb();

#endif
