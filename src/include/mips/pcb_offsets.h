#ifndef __PCB_OFFSETS_H_
#define __PCB_OFFSETS_H_

/*Sizes of the PCB components*/
#define PID_SIZE        0x4
#define STATE_SIZE      0x4
#define CONTEXT_SIZE    0x70    //  Size of $v0, $v1, $a0-$a3, $t0-$t9, $s0-$s7, $gp, $fp, $ra, $sp
#define STACK_SIZE      0x1000  //  1kB stack
//#define TEXT_SIZE       0x1000  //  1kB .text segment
//#define DATA_SIZE       0x1000  //  1kB .data segment
//#define SCHEDULE_SIZE   0x8     //  Next and previous pointers

/*The full size of the Memory Image*/
#define MEM_IMAGE_SIZE STACK_SIZE //+ TEXT_SIZE + DATA_SIZE

/* The full size of a PCB*/
#define PCB_SIZE PID_SIZE + STATE_SIZE + CONTEXT_SIZE + MEM_IMAGE_SIZE

/* Adress offsets*/
#define CONTEXT_OFFSET  PID_SIZE + STATE_SIZE
#define STACK_OFFSET    CONTEXT_OFFSET + CONTEXT_SIZE

#endif
