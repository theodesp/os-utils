# boot:
A collection of boot loaders and simple programs that are bootable as sectors

## Usage:
Compile and run with qemu

```bash
nasm boot_{target}.asm -f bin -o boot_{target}.bin

qemu-system-{your architecture} boot_{target}.bin
```

## Targets:
* boot_sector: Constructs an empty bootable sector that does nothing
* boot_hello_world: Constructs a bootable sector that prints "hello" using the
BIOS teletype output. See [BIOS interrupts](https://en.wikipedia.org/wiki/INT_10H)
