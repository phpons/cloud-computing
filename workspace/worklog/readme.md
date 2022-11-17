# Before everything, some of my notes:
## Previous level of experience:
I had some previous experience with Docker and Kubernetes before this class, but not much at all with Asm and this kind of low level work.

# Week 1 - progress:
* The incremental progress can be better followed in the "Week1 - Answers.md" file. *

# Console
## Commands:
Echo and reset were successfully implemented. One improvement could be to beautify the console, but I chose not to do it due to time constraints.

## Arrow navigation:
Navigation with left and right arrows is also working, however it doesn't *perfectly* simulate a terminal line. Going left or right in this console is akin to going left or right directly on the string; that is, writing on a certain position will not push the rightmost characters of a string, it will replace them.

## History:
The history was implemented with up and down arrow movement. The functionality is very similar to a common terminal, except for the fact that you can scroll through empty lines in the history.

# Week 2
WIP