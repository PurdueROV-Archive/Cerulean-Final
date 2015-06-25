#Packet Spec

Byte # | Description | Type
-------|-------------|------
  00   |   Header    | 0x12 - 18 decimal
  01   |   Motor 1   | Signed int (1 byte)   
  02   |   Motor 2   | Signed int (1 byte)   
  03   |   Motor 3   | Signed int (1 byte)   
  04   |   Motor 4   | Signed int (1 byte)   
  05   |   Motor 5   | Signed int (1 byte)   
  06   |   Motor 6   | Signed int (1 byte)   
  07   |   Motor 7   | Signed int (1 byte)   
  08   |   Motor 8   | Signed int (1 byte)   
  09   | Foot Turner | Signed int (1 byte)  
  10   |   Tools 1   | 1 bit more each state of tool (check below)  
  11   |   Stepper   | 1 byte (check below) for laser tool  
  12   |    LED1     | 1 byte (0 to 255 PWM Val)  
  13   |    LED2     | 1 byte (0 to 255 PWM Val)  
  14   |    LED3     | 1 byte (0 to 255 PWM Val)  
  15   |    LED4     | 1 byte (0 to 255 PWM Val)  
  16   |    LED5     | 1 byte (0 to 255 PWM Val)  
  17   |   Command   | 0x01 == Control
  18   | CRC8 Check  | (use 0xD5 as polynomial) 
  19   | Tail Byte   | 0x13 - 19 decimal  
  
Always set command to 0x01. In the future, there will be further options to program options are ask for certain data using this byte, but nothing is set yet.  


Motor signed bit representation (and foot turner)  
Use bit masking to get the sign bit, and then the motor value 
Scale the percentage from 0 to 127 to 0% to 100%  

Bit Values | Dec Value | Motor Percent 
-----------|-----------|---------------
0000 0000  |         0 |            0
0000 0001  |         1 |            1
0111 1111  |       127 |          100
1000 0000  |       128 |           -0
1000 0001  |       129 |           -1
1111 1111  |       255 |         -100


Tool Representation (Subject to change depending on tools)  
Use bit masking to get off the values you need (magic!)  

Tool Byte 1  

Bit # |    Tool   | State (0)  | State (1)  
------|-----------|------------|----------  
  1   | Cam Mux 1 |      Front | Back  
  2   | Cam Mux 2 |     Side 1 | Side 2
  3   |  Claw 1   |       Open | Close  
  4   | Stepper 0 |    Nothing | Set reported angle to 0  
  5   |   Bilge   |        Off | On  
  6   |    N/A    |        N/A | N/A  
  7   |   Volt    |        Off | On 
  8   |   Laser   |        Off | On  



If both bits for Bilge and Claw are set to 1, do nothing (must be an exclusive or to have an action)  
   

Laser Tool: 1 bit for controller whether the horizontal or vertical  
stepper move l/r and 3 bits for 0 to 7 steps to move

Bit # | State (0)  | State (1)  
------|------------|----------
  1   | H - Left   | H - Right
  2   | Step Amnt  | Step Amnt
  3   | Step Amnt  | Step Amnt
  4   | Step Amnt  | Step Amnt
  5   | V - Left   | V - Right
  6   | Step Amnt  | Step Amnt
  7   | Step Amnt  | Step Amnt
  8   | Step Amnt  | Step Amnt
  
#Return Packet

Byte # |   Description  | Type
-------|----------------|------
  00   |     Header     | 0x12 - 18 decimal
  01   |   V STP ANGL   | Signed int (1 byte)
  02   |   H STP ANGL   | Signed int (1 byte)   
  03   |   Fuse Detect  | Fuses
  04   |    MC Faults   | 2 bits per motor (4)
  05   |    MC Faults   | 2 bits per motor (4)
  06   |     Laser      | TBD 
  07   |     Laser      | TBD
  08   |     Misc       | TBD
  09   |   CRC8 Check   | (use 0xD5 as polynomial) 
  10   |   Tail Byte    | 0x13 - 19 decimal  

CRC8 Code: this code ignores the first byte (header), and the last byte (Tail).  
Make sure that the CS values is set to "0xC5" before running the code through.

```c
char crc8(char bytes[], int size) {
  char crc = 0;
  char val;
  char mix;
  for (int i = 1; i < size - 2; ++i) {
    val = bytes[i];
    for (int j = 8; j; --j) {
      mix = (crc ^ val) & 0x01;
      crc >>= 1;
      if (mix) {
        crc ^= 0xD5;
      }
      val >>= 1;
    }
  }
  return crc;
}
```
