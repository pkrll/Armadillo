PHONY: run debug gdb objdump symbols docs style clean

CC = mipsel-elf
CFLAGS = -g -Wall -Wextra -Werror -nostdlib -fno-builtin
AFLAGS = --gen-debug -mips32
VM = qemu-system-mipsel
VMFLAGS = -M malta -m 256 -serial stdio -device usb-mouse -device usb-kbd -show-cursor -display sdl
VMFLAGS_DEBUG = -M malta -m 256 -s -S

ELF_NAME = uphill.elf

# Directories

SRC_DIR = src
KER_SRC = $(SRC_DIR)/kernel
CMN_SRC = $(SRC_DIR)/common
INC_DIR = $(SRC_DIR)/include
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files

HEADER_SOURCES=$(wildcard $(INC_DIR)/*.h)
KERNEL_SOURCES=$(wildcard $(KER_SRC)/*.c)
COMMON_SOURCES=$(wildcard $(CMN_SRC)/*.c)
ASSEMBLY_SOURCES=$(wildcard $(KER_SRC)/*.S)

OBJECTS = $(patsubst $(KER_SRC)/%.c, $(OBJ_DIR)/%.o, $(KERNEL_SOURCES))
OBJECTS += $(patsubst $(CMN_SRC)/%.c, $(OBJ_DIR)/%.o, $(COMMON_SOURCES))
OBJECTS += $(patsubst $(KER_SRC)/%.S, $(OBJ_DIR)/%.o, $(ASSEMBLY_SOURCES))

# Files to clean up
CLEAN_FILES = $(shell find . -type f -name '*.orig')

all:
	@echo "usage: make [build|compile|run|debug|gdb|objdump|symbols|clean]"

build: $(BIN_DIR)/$(ELF_NAME)

compile: $(OBJECTS)
	@echo "Compilation done..."

$(OBJ_DIR)/%.o: $(KER_SRC)/%.c
	$(CC)-gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(CMN_SRC)/%.c
	$(CC)-gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.s: $(KER_SRC)/%.S
	$(CC)-gcc -I $(INC_DIR) -E -o $@ $<

$(OBJ_DIR)/%.o: $(OBJ_DIR)/%.s
	$(CC)-as $(AFLAGS) -o $@ $<

$(BIN_DIR)/$(ELF_NAME): $(OBJECTS)
	@echo "Linking the kernel..."
	$(CC)-ld -T $(SRC_DIR)/linker.ld -o $(BIN_DIR)/$(ELF_NAME) $(OBJECTS)

run: $(BIN_DIR)/$(ELF_NAME)
	@echo "Running $(ELF_NAME) on qemu with flags: $(VMFLAGS)"
	@$(VM) $(VMFLAGS) -kernel $(BIN_DIR)/$(ELF_NAME)

#######################
# Unit testing
#######################

TEST_DIR = tests
TKER_DIR = $(TEST_DIR)/kernel
TEST_INC = $(TEST_DIR)/include
TEST_KERNEL = $(OBJ_DIR)/test_boot.o $(OBJ_DIR)/test_exception.o $(OBJ_DIR)/test_kernel.o $(OBJ_DIR)/test_main.o

$(OBJ_DIR)/%.o: $(TKER_DIR)/%.c
	$(CC)-gcc -I $(INC_DIR) -I $(TEST_INC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.s: $(TKER_DIR)/%.S
	$(CC)-gcc -I $(INC_DIR) -E -o $@ $<

$(OBJ_DIR)/%.o: $(OBJ_DIR)/%.s
	$(CC)-as $(AFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC)-gcc -I $(INC_DIR) -I $(TEST_INC) $(CFLAGS) -o $@ -c $<

test: $(BIN_DIR)/armadillo_test

$(BIN_DIR)/armadillo_test: $(TEST_KERNEL) $(OBJ_DIR)/stdio.o $(OBJ_DIR)/stdlib.o $(OBJ_DIR)/test_stdlib.o $(OBJ_DIR)/memory.o $(OBJ_DIR)/test_memory.o $(OBJ_DIR)/pcb.o $(OBJ_DIR)/queue.o $(OBJ_DIR)/dispatcher.o $(OBJ_DIR)/test_dispatcher.o
	$(CC)-ld -T $(TEST_DIR)/linker.ld -o $@ $^
	@$(VM) $(VMFLAGS) -kernel $@

#######################
# Debugging
#######################

debug: $(BIN_DIR)/$(ELF_NAME)
	@echo "Running $(ELF_NAME) on qemu with flags: $(VMFLAGS_DEBUG)"
	@$(VM) $(VMFLAGS_DEBUG) -kernel $(BIN_DIR)/$(ELF_NAME)

gdb: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-gdb --symbols=$(BIN_DIR)/$(ELF_NAME) -ex "target extended-remote :1234" -ex "layout regs"

objdump: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-objdump -D bin/uphill.elf > $(BIN_DIR)/uphill.asm

symbols: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-nm -n $(BIN_DIR)/$(ELF_NAME)

#######################
# Documentation
#######################

documentation:
	doxygen Doxyfile

style:
	astyle --style=google --indent=tab=2 --indent-continuation=2 $(KERNEL_SOURCES) $(COMMON_SOURCES)

clean:
	rm -rf bin/*
	rm -rf obj/*
ifneq ($(CLEAN_FILES), )
	rm -f $(CLEAN_FILES)
endif
