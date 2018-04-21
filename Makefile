CC = mipsel-elf
CFLAGS = -g -Wall -Wextra -Werror -nostdlib -fno-builtin
TFLAGS= -lcunit #-lm --coverage # lm needed to link math lib

VM = qemu-system-mipsel
VMFLAGS = -M malta -m 256 -serial stdio

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
	@echo "Sorry, nothing to do yet"

build: compile
	@echo "Linking the kernel..."
	$(CC)-ld -T $(SRC_DIR)/linker -o $(BIN_DIR)/$(ELF_NAME) $(OBJECTS)

compile: $(OBJECTS)

$(OBJ_DIR)/%.o: $(KER_DIR)/%.c
	$(CC)-gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(KER_DIR)/%.S
	$(CC)-as -o $@ $<

run:
	@echo "Running $(ELF_NAME) on qemu with flags: $(VMFLAGS)"
	@$(VM) $(VMFLAGS) -kernel $(BIN_DIR)/$(ELF_NAME)

test: test_stack

test_stack: $(OBJ_DIR)/stack.o $(OBJ_DIR)/stack_test.o
	gcc -I/usr/local/Cellar/cunit/2.1-3/include -L/usr/local/Cellar/cunit/2.1-3/lib $(OBJ_DIR)/stack.o $(OBJ_DIR)/stack_test.o -o $(BIN_DIR)/test_queue $(TFLAGS)

clean:
	rm -rf bin/*
	rm -rf obj/*
