# Project Report
## Previous level of experience:
I had some previous experience with Docker and Kubernetes before this class, but not much at all with Asm and this kind of low level work.

# How to compile and run
The command *make run* should be enough to compile and run the code. 

## Running the code of week 1.
To run the complete code of week 1, you should use the exact code from the tag "step4". The code from week 2 is not fully functional with the console.

## Running the code of week 2.
To run the code of week 2, use the tag "week2", which should be the most recent commit.

# What works - Week 1
*The incremental progress can be better followed in the "Week1 - Answers.md" file.*

Basically, everything works for the requirements of week 1. The behavior of a modern terminal is not 100% matched due to some details; improvements will be discussed in the specific sections.

## Console
### Commands:
The commands echo and reset were successfully implemented. I don't think anything could be improved in this case.

### Arrow navigation:
Navigation with left and right arrows is functional, however it doesn't **perfectly** simulate a terminal line; that is, going left or right in this console is akin to going left or right directly on the string; that is, writing on a certain position will not push the rightmost characters of a string, it will replace them.

Up and down navigation is implemented and controls the history functionality:

### History:
The history was implemented with up and down arrow movement. The functionality is very similar to a common terminal, except for the fact that you can scroll through empty lines in the history.

# Before everything, some of my notes:
## Previous level of experience:
I had some previous experience with Docker and Kubernetes before this class, but not much at all with Asm and this kind of low level work.

# What works - Week 2:
## Disclaimer
**I was not able to successfully implement all functionalities of week 2, so the console (procesing commands) is not enabled. To run the console, the week 1 tag should be used instead, as explained in the sections above.**

## Enabling interruptions
The interruptions and FIFO were successfully enabled, as can be confirmed by running the code and checking that (at least) timeout interruptions are being captured.

This required allocating space in the stack for IRQ and executing the lines of code provided in the Week 2's README.

## Writing to circular buffers
I was able to use the RX and TX circular buffers in the code. The RX is used as specified; it is filled when a interruption is triggered. The TX buffer, although implemented, ended up not being used as I was not able to detected transmit interruptions.

## Capturing interruptions
Although the code was able to detect/capture receive interruptions, for some reason transmit interruptions were not being captured. From my understanding of the README,

>The function "uart_send" will push bytes in another circula buffer,
called "txcb", that the handler of the TX interrupt will...

the interruption should be triggered when the TX circular buffer is full. However, I do not see how the hardware could detect that this buffer is full since it is defined by us in the code. I think I missed something here.



# What does not work - Week 2:
- Transmitting is still done using the "conventional" method for the reasons explained above, although the code for the interruption method is partially implemented
- At some point while receiving, errors will start occurring or the terminal will freeze. I did not find a way to fix this error.
