PHONY: run debug gdb objdump symbols docs style clean

CC = mipsel-elf
CFLAGS = -g -Wall -Wextra -Werror -nostdlib -fno-builtin
AFLAGS = --gen-debug -mips32
VM = qemu-system-mipsel
VMFLAGS = -M malta -m 256 -serial stdio
VMFLAGS_DEBUG = -M malta -m 256 -monitor stdio -s -S

ELF_NAME = uphill.elf

# Directories

SRC_DIR = src
KER_SRC = $(SRC_DIR)/kernel
INC_DIR = $(SRC_DIR)/include
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files

HEADER_SOURCES=$(wildcard $(INC_DIR)/*.h)
KERNEL_SOURCES=$(wildcard $(KER_SRC)/*.c)
ASSEMBLY_SOURCES=$(wildcard $(KER_SRC)/*.S)

OBJECTS = $(patsubst $(KER_SRC)/%.c, $(OBJ_DIR)/%.o, $(KERNEL_SOURCES))
OBJECTS += $(patsubst $(KER_SRC)/%.S, $(OBJ_DIR)/%.o, $(ASSEMBLY_SOURCES))


all:
	@echo "usage: make [build|compile|run|debug|gdb|objdump|symbols|clean]"

build: $(BIN_DIR)/$(ELF_NAME)

compile: $(OBJECTS)

$(OBJ_DIR)/%.o: $(KER_SRC)/%.c
	$(CC)-gcc -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.s: $(KER_SRC)/%.S
	$(CC)-gcc -I $(INC_DIR) -E -o $@ $<

$(OBJ_DIR)/%.o: $(OBJ_DIR)/%.s
	$(CC)-as $(AFLAGS) -o $@ $<

$(BIN_DIR)/$(ELF_NAME): $(OBJECTS)
	@echo "Linking the kernel..."
	$(CC)-ld -T $(SRC_DIR)/linker -o $(BIN_DIR)/$(ELF_NAME) $(OBJECTS)

run: $(BIN_DIR)/$(ELF_NAME)
	@echo "Running $(ELF_NAME) on qemu with flags: $(VMFLAGS)"
	@$(VM) $(VMFLAGS) -kernel $(BIN_DIR)/$(ELF_NAME)

debug: $(BIN_DIR)/$(ELF_NAME)
	@echo "Running $(ELF_NAME) on qemu with flags: $(VMFLAGS_DEBUG)"
	@$(VM) $(VMFLAGS_DEBUG) -kernel $(BIN_DIR)/$(ELF_NAME)

gdb: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-gdb --symbols=$(BIN_DIR)/$(ELF_NAME) -ex "target extended-remote :1234" -ex "layout regs"

objdump: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-objdump -D bin/uphill.elf > $(BIN_DIR)/uphill.asm

symbols: $(BIN_DIR)/$(ELF_NAME)
	mipsel-elf-nm -n $(BIN_DIR)/$(ELF_NAME)

Doxyfile:
	doxygen -g Doxyfile

docs: Doxyfile
	doxygen Doxyfile

style:
	astyle --style=google --indent=tab=2 --indent-continuation=2 $(KERNEL_SOURCES)

clean:
	rm -rf bin/*
	rm -rf obj/*
