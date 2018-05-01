#ifndef __DISPATCHER_H_
#define __DISPATCHER_H_

#include <common/stdlib.h>
#include <common/pcb.h>
#include <common/screen.h>

__attribute__((unused))static addr_t process_mem_space __attribute__((section(".bss"))); //Berätta för assebly var denna finns
void dispatcher_init();
void process_switch();
pcb_t *get_current_pcb();

#endif
