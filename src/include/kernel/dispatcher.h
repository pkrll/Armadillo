/**
 * @file
 * @brief Dispatcher
 */

#ifndef __DISPATCHER_H_
#define __DISPATCHER_H_

#include <kernel/pcb.h>
#include <common/stdlib.h>
#include <common/stdio.h>
#include <common/memory.h>
#include <common/queue.h>

//__attribute__((unused))static addr_t process_mem_space __attribute__((section(".bss")));

/**
 * Allocates the ready queue and initializes all processes.
 */
void dispatcher_init();
/**
 * Enqueues the running process into the ready queue, pops another process
 * from the queue and assigns it as the running process.
 */
void process_switch();
/**
 * Returns the adress for the PCB of the currently running process.
 *
 * @return Adress of the current process' PCB
 */
pcb_t *get_current_pcb();

//So we can start the first process in kernel. We need to do that so we can make tests for dispatcher_init. Can remove this if we find a better way.
void process_0();

void spawn_process();


#endif
