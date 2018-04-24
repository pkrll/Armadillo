#ifndef __PCB_H_
#define __PCB_H_

#define PID_SIZE        0x4
#define STATE_SIZE      0x4
#define CONTEXT_SIZE    0x70    //  Size of $v0, $v1, $a0-$a3, $t0-$t9, $s0-$s7, $gp, $fp, $ra, $sp
#define STACK_SIZE      0x1000  //  1kB stack
#define TEXT_SIZE       0x1000  //  1kB .text segment
#define DATA_SIZE       0x1000  //  1kB .data segment
#define MEM_IMAGE_SIZE  STACK_SIZE + TEXT_SIZE + DATA_SIZE
#define SCHEDULE_SIZE   0x8     //  Next and previous pointers

#define PCB_SIZE PID_SIZE + STATE_SIZE + CONTEXT_SIZE + MEM_IMAGE_SIZE + SCHEDULE_SIZE

#define CONTEXT_OFFSET PID_SIZE + STATE_SIZE
#define PC_OFFSET PID_SIZE + STACK_SIZE + CONTEXT_SIZE + STACK_SIZE + TEXT_SIZE + DATA_SIZE + MEM_IMAGE_SIZE + SCHEDULE_SIZE
#define STACK_OFFSET PID_SIZE + STATE_SIZE + CONTEXT_SIZE
#endif
