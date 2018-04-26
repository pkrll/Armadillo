#ifndef __DISPATCHER_H_
#define __DISPATCHER_H_

#include <common/stdlib.h>
#include <common/pcb.h>

__attribute__((unused))static addr_t process_mem_space __attribute__((section(".bss"))); //Berätta för assebly var denna finns
void dispatcher_init();
void process_switch();

#endif
