CC = mipsel-elf
CFLAGS = -g -Wall -Wextra -Werror -nostdlib -fno-builtin
TFLAGS= -lcunit #-lm --coverage # lm needed to link math lib
AFLAGS = --gen-debug -mips32

VM = qemu-system-mipsel
VMFLAGS = -M malta -m 256 -serial stdio
VMFLAGS_DEBUG = -M malta -m 256 -monitor stdio -s -S

ELF_NAME = uphill.elf

# Directories

SRC_DIR = src
KER_DIR = $(SRC_DIR)/kernel
INC_DIR = $(SRC_DIR)/include
LIB_DIR = $(SRC_DIR)/lib
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test
# Source and object files

KERNEL_SOURCES=$(wildcard $(KER_DIR)/*.c)
LIBRARY_SOURCES=$(wildcard $(LIB_DIR)/*.c)
ASSEMBLY_SOURCES=$(wildcard $(KER_DIR)/*.S)
TEST_SOURCES=$(wildcard $(TEST_DIR)/*.c)

OBJECTS = $(patsubst $(KER_DIR)/%.c, $(OBJ_DIR)/%.o, $(KERNEL_SOURCES))
# OBJECTS += $(patsubst $(LIB_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIBRARY_SOURCES))
OBJECTS += $(patsubst $(KER_DIR)/%.S, $(OBJ_DIR)/%.o, $(ASSEMBLY_SOURCES))

all:
	@echo "usage: make [build|compile|run|debug|gdb|objdump|symbols|clean]"

build: $(BIN_DIR)/$(ELF_NAME)

compile: $(OBJECTS)

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(KER_DIR)/%.c
	$(CC)-gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.s: $(KER_DIR)/%.S
	$(CC)-gcc -I $(INC_DIR) -E -o $@ $<

$(OBJ_DIR)/%.o: $(OBJ_DIR)/%.s
	$(CC)-as $(AFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(BIN_DIR)/$(ELF_NAME): $(OBJECTS)
	@echo "Linking the kernel..."
	$(CC)-ld -T $(SRC_DIR)/linker -o $(BIN_DIR)/$(ELF_NAME) $(OBJECTS)

run: $(BIN_DIR)/$(ELF_NAME)
	@echo "Running $(ELF_NAME) on qemu with flags: $(VMFLAGS)"
	@$(VM) $(VMFLAGS) -kernel $(BIN_DIR)/$(ELF_NAME)

test: test_stack
	./bin/test_stack

test_stack: $(OBJ_DIR)/stack.o $(OBJ_DIR)/stack_test.o
	gcc -I/usr/local/Cellar/cunit/2.1-3/include -L/usr/local/Cellar/cunit/2.1-3/lib $(OBJ_DIR)/stack.o $(OBJ_DIR)/stack_test.o -o $(BIN_DIR)/test_stack $(TFLAGS)

debug: $(BIN_DIR)/$(ELF_NAME)
	@echo "Running $(ELF_NAME) on qemu with flags: $(VMFLAGS_DEBUG)"
	@$(VM) $(VMFLAGS_DEBUG) -kernel $(BIN_DIR)/$(ELF_NAME)

gdb: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-gdb --symbols=$(BIN_DIR)/$(ELF_NAME) -ex "target extended-remote :1234" -ex "layout regs"

objdump: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-objdump -D bin/uphill.elf > $(BIN_DIR)/uphill.asm

symbols: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-nm -n $(BIN_DIR)/$(ELF_NAME)

clean:
	rm -rf bin/*
	rm -rf obj/*
