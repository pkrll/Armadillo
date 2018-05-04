# Armadillo

__OSPP (1DT096) 2018 - Project iota__

Armadillo is a very simple operating system for the MIPS Malta board, created as a group project in _Operating systems and process oriented programming_ (1DT096), spring 2018, _Uppsala university_.

**TODO:** Lägg till en kort beskrivning av projektet.

**TODO:** Länk(ar) till mer utförlig dokumentation. (Doxygen dokumentation + Wiki?)

## Prerequisites

* Mipsel-elf cross compiler (See [How to build a cross compiler](#todo))
* Qemu (Developed using version 2.11.1)
* GDB cross compiled for mipsel-elf. (See [How to cross build GDB](#todo))

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

## Struktur

```bash
.
├── Doxyfile
├── Makefile
├── README.md
├── bin
├── docs
├── guidelines
├── meta
├── obj
├── src
│   ├── common
│   ├── include
│   │   ├── common
│   │   ├── mips
│   │   └── test
│   ├── kernel
│   │   ├── boot.S
│   │   ├── exceptions.S
│   │   ├── kernel.c
│   │   └── timer.S
│   └── linker.ld
└── tests
```

## Färdigställ

- [ ] Allt eftersom projektet fortskrider kan ni lägga till fler rubriker i detta dokument med kompletterande information.
- [ ] Färdigställ dokumentet [meta/gruppkontrakt.md](./meta/gruppkontrakt.md).
* [x] Färdigställ dokumentet [meta/medlemmar.md](./meta/medlemmar.md).
* [ ] Tag bort alla stycken markerade med **TODO** och **INFO**.
* [ ] Tag bort hela detta avsnitt, dvs tag bort avsnittet **Färdigställ**.
