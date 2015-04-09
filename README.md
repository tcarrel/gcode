# gcode
A program to interpret and run gcode on a Raspberry Pi.

# Intent
To run two servos connected to a lathe for CNC machining.  I eventually hope to add axes to enable to control servos on more complex machines such as mills and 3D printers.

# Basic operation
Reads a gcode file from disk and adds machining commands one-by-one to a linked list, checking for possible errors as they are added.  The commands can then be run at user request if no errors were encountered during loading.
