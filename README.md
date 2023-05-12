# CS 745 - Principles of Data and System Security

This repository contains the code for the course project of CS 745.

The topic chosen for this project is Buffer Overflow in a Heap.

Buffer overflow in Heap has been exploited in two ways:
- Metadata Corruption
- Vtable Hijacking

### Vtable Hijacking

The program successfully replaces the vpointer of an object neighbouring a chunk in which buffer overflow occured. With that, the flow of program was successfully diverted.

### Metadata Corruption

The program successfully corrupts the metadata of the neighbouring chunk by buffer overflow in the previous chunk. However, the target of obtaining an arbitrary pointer after the next malloc was not met as the corruption of metadata was detected and the program aborted. The problems due to buffer overflow have been tackled by a number of ways and hence, the exploit could not be completely demonstrated.
