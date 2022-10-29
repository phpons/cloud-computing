# Week 1 - Step 1

## 1. Make sure you can compile and run for both boards: VAP and VPB.
Same processor? Same amount of memory?
 
- Both can be compile and run. 
- VAP and VPB have different specifications, notably different CPUs and different amounts of memory (1M vs. 32M).

## 2.1. Understand the linker script and the memory map relationship. Understand the BSS section and why it needs to be reset to 0.

- The linker script is defining the entry point of the code and positioning memory sections (such as the code, data, bss...). 

- The bss section is reset to 0 because it is used for uninitialized data or data initialized to 0, therefore having leftover data in that memory section could be a problem (this is what seems logical to me, I couldn't find the answer anywhere).

## 2.2. Create global variables; some initalized and some uninitialized. Confirm you understand the relationship between these global variables and the different data sections.
- Global data initialized to 0 or uninitialized will go to .bss (as it is guaranteed to be zeroed), the other variables are assigned to the .data section.

## 2.3. Experiment with "arm-none-eabi-objdump" to look at what the compiler does, both on object files and on the file ELF executable.
By running arm-none-eabi-objdump -D kernel.elf, we can see the sections are perfectly organized according to the linker script, which is kinda cool. Other than that, I did not extract much additional information.

## 2.4. Why is the bss section aligned on a 16-byte boundary? Confirm you see why in the code in the file "reset.s".
- It is done because 16B are zeroed at a time. 
- ASM is writing to 4 registers at a time, each register is of 4B size, therefore 16B.

# Week 2 - Step 2
> Understand the boot sequence, following the execution step by step under gdb. The use of gdb is MANDATORY!

Sure. To debug, we can follow these steps:
1. Run make debug (creates debugging session on :1234)
2. Run
    1. arm-none-eabi-gdb
    2. file kernel.elf
    3. target remote localhost:1234
3. From here onwards, just add breaks wherever you want and watch the execution with si (or list).

The boot sequence goes just as expected; we run one instruction on vector.s loading the pc, then go off to reset.s.

> Verify that what you see corresponds to your understanding of the linker script and the memory map.

So far so good :). The command *info registers* also let me take a look at the registers, quite cool not gonna lie. 

> Remove the periodic "Zzzz..." output. Why was it there?  
What does that tell you about the execution?



