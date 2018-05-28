# Armadillo

__OSPP (1DT096) 2018 - Project iota__

Armadillo is a very simple operating system for the MIPS Malta board, created as a group project in _Operating systems and process oriented programming_ (1DT096), spring 2018, _Uppsala university_.

## Prerequisites

* Mipsel-elf cross compiler (See [GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler))
* Qemu (Developed using version 2.11.1)
* GDB cross compiled for mipsel-elf. (See [Cross build GDB](https://www.linux-mips.org/wiki/Toolchains#GDB))

## Getting started

The ``Makefile`` includes a bunch of rules to build, compile, run and test the system.

##### Compile

To compile the project, use ``compile``. This  compiles and creates object files in the ``obj`` directory, but does not build a binary.

```bash
> make compile
Compilation done...
```

##### Link and build

To create a binary, use the rule ``make build``. This will, if necessary, compile and link the object files.

```bash
> make build
Linking the kernel...
```

##### Run

You can run Armadillo using the QEMU emulator.

```bash
> make run
Running armadillo.elf on qemu with flags: -M malta -m 256 -serial stdio
```

##### Tests

Unit tests are included. Run them with ``test``.

```bash
> make test
...
All tests passed!
```

##### Debug

Debugging Armadillo requires ``GDB``. Start by running the OS in debug mode, and then send the job to the background before starting ``GDB``:

```bash
> make debug
[ctrl+z]
> bg
> make gdb
```

## Structure

```bash
.
├── Doxyfile
├── Makefile
├── README.md
├── bin
├── docs
├── guidelines
│   ├── git.md
│   └── styleguide.md
├── meta
│   ├── gruppkontrakt.md
│   ├── medlemmar.md
│   └── meetings
├── obj
├── src
│   ├── common
│   │   ├── k_rand.c
│   │   ├── memory.c
│   │   ├── queue.c
│   │   ├── stack.c
│   │   ├── stdio.c
│   │   └── stdlib.c
│   ├── include
│   │   ├── common
│   │   │   ├── k_rand.h
│   │   │   ├── math.h
│   │   │   ├── memory.h
│   │   │   ├── processes.h
│   │   │   ├── queue.h
│   │   │   ├── stack.h
│   │   │   ├── stdint.h
│   │   │   ├── stdio.h
│   │   │   └── stdlib.h
│   │   ├── kernel
│   │   │   ├── dispatcher.h
│   │   │   ├── exceptions.h
│   │   │   └── pcb.h
│   │   └── mips
│   │       ├── adresses.h
│   │       ├── bitmasks.h
│   │       └── registers.h
│   ├── kernel
│   │   ├── boot.S
│   │   ├── context_switch.S
│   │   ├── dispatcher.c
│   │   ├── exceptions.S
│   │   ├── kernel.c
│   │   ├── pcb.c
│   │   ├── processes.c
│   │   ├── rand.S
│   │   └── timer.S
│   └── linker.ld
└── tests
    ├── include
    │   ├── munit
    │   │   └── unit.h
    │   ├── test_dispatcher.h
    │   ├── test_memory.h
    │   ├── test_stack.h
    │   └── test_stdlib.h
    ├── kernel
    │   ├── test_boot.S
    │   ├── test_exception.S
    │   └── test_kernel.c
    ├── linker.ld
    ├── test_dispatcher.c
    ├── test_main.c
    ├── test_memory.c
    ├── test_stack.c
    └── test_stdlib.c
```

## Documentation

Here you'll find the documentation for Armadillo, along with some useful links.

* [Armadillo documentation](https://uu-os-2018.github.io/project-iota/)
* [GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler)
