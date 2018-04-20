#ifndef __PCB_H_
#define __PCB_H_

#define PID_SIZE        0x4
#define STATE_SIZE      0x4
#define CONTEXT_SIZE    0x6C      //  Size of $v0, $v1, $a0-$a3, $t0-$t9, $s0-$s7, $gp, $fp, $ra
#define STACK_SIZE      0x100000  //  1MB stack
#define TEXT_SIZE       0x100000  //  1MB .text segment
#define DATA_SIZE       0x100000  //  1MB .data segment
#define MEM_IMAGE_SIZE  STACK_SIZE + TEXT_SIZE + DATA_SIZE
#define SCHEDULE_SIZE   0x8       //  Next and previous pointers
#define PC_SIZE         0x4
#define SP_SIZE         0x4

#define PCB_SIZE PID_SIZE + STATE_SIZE + CONTEXT_SIZE + MEM_IMAGE_SIZE + SCHEDULE_SIZE + PC_SIZE + SP_SIZE

#define CONTEXT_OFFSET PID_SIZE + STATE_SIZE
#endif
