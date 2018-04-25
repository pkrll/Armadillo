#include "common/pcb.h"

enum state{
  ready = 0,
  running = 1,
};

struct context{
  reg_t sp;
  reg_t ra;
  reg_t t0;
  reg_t t1;
  reg_t t2;
  reg_t t3;
  reg_t t4;
  reg_t t5;
  reg_t t6;
  reg_t t7;
  reg_t t8;
  reg_t t9;
  reg_t v1;
  reg_t v0;
  reg_t a0;
  reg_t a1;
  reg_t a2;
  reg_t a3;
  reg_t s0;
  reg_t s1;
  reg_t s2;
  reg_t s3;
  reg_t s4;
  reg_t s5;
  reg_t s6;
  reg_t s7;
  reg_t gp;
  reg_t fp;
  reg_t pc;
};

struct pcb{
  pid_t pid;
  state_t process_state;
  context_t cpu_context;
  addr_t stack;
  addr_t text_seg;
  addr_t data_seg;
  addr_t schedule_info;
};
