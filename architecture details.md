# Implementation details for architecture

## Opcodes for:  
* Addition                      <!-- For basic pointer management -->
* Subtraction                   <!-- For basic pointer management -->
* jump                          <!-- For if/else , loops and function calls-->
* less than                     <!-- For if/else and loops -->
* assignment using direct value <!-- Move immidiate -->
* assignment using variable     <!-- Move via reference-->
* bitshift                      <!-- For divide by 2 functionality-->

## Control Signals, multiplexes, and other information, helps in specifying the state of architecture

* signalGUI:                    If high, defers that the control is with GUI and no action is being performed (GUI valo...start button dabao)  
* signalRD:                     If high, then processor is busy reading from RAM  
* signalWR:                     If high, then processor is busy writing to RAM  
* multiplexALU:                 1 byte register, if non zero, Defines what operation is to be performed by ALU, else, control is not given to ALU  
* registerInstruction:          1 byte register, that holds current OPCODE
* registerA:                    1 byte Accumulator
* registerB:                    1 byte General purpose Register
* registerD:                    1 byte General purpose Register
* Stack Pointer:                    1 byte General purpose Register
* Return Address:                   1 byte hidden register, stores return address for current call 

## Memory:
### 2 segments
Total size of 256 B
1. Code Segment: 
    * First 128 Bytes
    * Stores the source code  
2. Data Segment:
    * Last 128 Bytes
    * Stores data, like inputs, variables etc.