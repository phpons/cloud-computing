# Week 1 - Step 1

> 1 - Make sure you can compile and run for both boards: VAP and VPB.
Same processor? Same amount of memory?
 
First off, both can be compiled and run. 


VAP and VPB have different specifications, notably different CPUs and different amounts of memory (1M vs. 32M).

> 2.1 - Understand the linker script and the memory map relationship. Understand the BSS section and why it needs to be reset to 0.

The linker script is defining the entry point of the code and positioning memory sections (such as the code, data, bss...). 

The bss section is reset to 0 because it is used for uninitialized data or data initialized to 0, therefore having leftover data in that memory section could be a problem (this is what seems logical to me, I couldn't find the answer anywhere).

<br>

> 2.2 - Create global variables; some initalized and some uninitialized. Confirm you understand the relationship between these global variables and the different data sections.

Global data initialized to 0 or uninitialized will go to .bss (as it is guaranteed to be zeroed), the other variables are assigned to the .data section.

> 2.3 - Experiment with "arm-none-eabi-objdump" to look at what the compiler does, both on object files and on the file ELF executable.

By running arm-none-eabi-objdump -D kernel.elf, we can see the sections are perfectly organized according to the linker script, which is kinda cool. Other than that, I did not extract much additional information.

>2.4. Why is the bss section aligned on a 16-byte boundary? Confirm you see why in the code in the file "reset.s".

It is 16-byte aligned because 16B are zeroed at a time. Reason being ASM is writing to 4 registers at a time, each register is of 4B size, therefore 16B.

# Week 1 - Step 2
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

The "deeper" purpose of this output remains a question for me. We're running an infinite loop in _start() and printing that message with *uart_send_string()* when we reach a certain count. Perhaps this is to illustrate that the main loop could eventually be interrupted for that output to be done instead of relying on sequential execution.

> Why is the symbol _stack_top defined and why is it at the end of
everything?

It is at the end because of how the stack is positioned in memory; it starts in a certain region (above the other mapped regions in this case) and grows downwards. The stack_top is also used to set the stack pointer register in *reset.s*.

> How can you verify in C that the stack is working properly?

You can verify it works by running any code that uses the stack; be it via calling functions or using local variables.

> What would happen if we were to call to many functions in C?

You would eventually run out of stack space and start writing to other sections of memory; a stack overflow would likely result in a program crash.


> How could you verify that your C program executes safely?

*(Not sure if I have interpreted this question correctly)*

You could use stack smashing protection mechanisms (well, any kind of buffer overflow protection). For instance, there could be a canary value that, once overwritten, indicates that a stack overflow has occurred; the OS can then handle the overflow accordingly.



> Had support for kprintf, see the file "kprintf.c".

**I am assuming that *had* meant *add*.**

*kprintf()* itself is already implemented in the code; *kputchar()* has to be implemented, which should be simple. For now I will leave kputchar pointing to UART0; I will also add kprintf.o to the makefile.

# Week 1 - Step 3

> Ask QEMU to emulate a second serial line, via a telnet connection.
See the makefile and the file "worklog/README-QEMU" for how to do this.

We have to add another (telnet) serial line in the makefile for this to work. This second serial line is "handled" by UART1.

> Direct kprintf to output via that second serial line, allowing you
to use kprintf to log stuff without compromising the "console".

This is done by directing the output to UART1 instead of UART0.

> Use that to print the byte values representing the encoding
of the typed characters on the keyboard. Watch what happens
when hitting regular letters, like 'a' 'b' 'A' and 'B'.
And then watch what happens when hitting special keys:

	- left,right,up, and down arrows
	- backspace
	- delete


The arrows, for instance, are composed by 3 different characters instead of just one. They are not a simple ASCII character.
- Up = 27 91 65
- Down = 27 91 66
- Right = 27 91 67
- Left = 27 91 68

# Week 1 - Step 4
> You will code the beginning of a console shell, on the 
serial line UART0. Upon startup, clear the screen, with
the cursor at the top-left corner.

This is can be done in Linux by printing a certain sequence of characters (thanks StackOverflow).

> The console introduces a command line behavior, like a 
regular shell. That is, the ability to edit a line before 
hitting "return", using the left and right arrow, 
and the backspace or delete keys.

This took a lot of work, but it is done.

> Once you have the ability to read an entire edited line,
when "return" is hit, you can introduce the parsing of that
line. First commands to parse:
  - the command "reset" that clears the entire screen,
    leaving the cursor at the top-left corner.
  - the command "echo" that echoes the rest of the line.    

Done.

> You will keep a history of the last 20 lines entered,
using up and down arrows to scroll through the history,
on the current line, like a regular shell would do.

Done. Reprinting the line from the history can be done via using a escape sequence and then just kprintf with the chosen line.