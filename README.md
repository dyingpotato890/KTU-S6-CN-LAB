# KTU S6 Networking LAB

This repository is dedicated to storing programs required for the Networking lab sessions conducted in Semester 6 for KTU students (2019 Syllabus).

## Table of Contents
- [Setup Instructions](#setup-instructions)
- [List of Experiments](#list-of-experiments)
- [Contributors](#contributors)

## Setup Instructions

1. **Install a Compiler/Interpreter:**
   - For C-based experiments, ensure a C compiler like GCC is installed on your system.
   - Use any text editor or IDE for coding (e.g., VS Code, Code::Blocks).
   
2. **Clone the Repository:**
   ```bash
   git clone https://github.com/dyingpotato890/KTU-S6-CN-LAB.git
   ```
3. **Navigate to the Directory:**
    ```bash
    cd KTU-S6-CN-LAB
   ```

## List of Experiments

1. [Networking Commands](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Networking%20Commands%20%26%20Configuration%20Files/Networking%20Commands%20-%20Output.txt) & [Network Configuration Files](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Networking%20Commands%20%26%20Configuration%20Files/Network%20Configuration%20Files%20-%20Output.txt)
       
2. Transaction Control Protocol (TCP):
   * Code:
     - [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Transaction%20Control%20Protocol/TCPserver.c)
     - [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Transaction%20Control%20Protocol/TCPclient.c)
   * [Output](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Transaction%20Control%20Protocol/TCPoutput.txt)
      
3. User Datagram Protocol (UDP):
   * Code:
     - [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/User%20Datagram%20Protocol/UDPserver.c)
     - [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/User%20Datagram%20Protocol/UDPclient.c)
   * [Output](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/User%20Datagram%20Protocol/UDPoutput.txt)
     
4. Sliding Window Protocols:
   * Go Back N ARQ:
     - Code: [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Go%20Back%20N%20ARQ/goBackARQServer.c) & [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Go%20Back%20N%20ARQ/goBackARQClient.c)
     - Output: [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Go%20Back%20N%20ARQ/serverOutput.txt) & [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Go%20Back%20N%20ARQ/clinetOutput.txt)
   * Selective Repeat ARQ:
     - Code: [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Selective%20Repeat%20ARQ/selRepARQServer.c) & [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Selective%20Repeat%20ARQ/selRepARQClient.c)
     - Output: [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Selective%20Repeat%20ARQ/serverOutput.txt) & [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Selective%20Repeat%20ARQ/clientOutput.txt)
   * Stop & Wait ARQ:
     - Code: [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Stop%20%26%20Wait%20ARQ/snwARQServer.c) & [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Stop%20%26%20Wait%20ARQ/snwARQClient.c)
     - Output: [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Stop%20%26%20Wait%20ARQ/serverOutput.txt) & [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Sliding%20Window%20Protocols/Stop%20%26%20Wait%20ARQ/clientOutput.txt)
     
5. File Transfer Protocol (FTP):
    * Code:
      - [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/File%20Transfer%20Protocol/serverFTP.c)
      - [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/File%20Transfer%20Protocol/clientFTP.c)
   * Output:
     - [Server](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/File%20Transfer%20Protocol/serverOutput.txt)
     - [Client](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/File%20Transfer%20Protocol/clientOutput.txt)
      
6. Leaky Bucket Algorithm: [Code](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Leaky%20Bucket%20Algorithm/leakyBucket.c) & [Output](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Leaky%20Bucket%20Algorithm/leakyBucketOutput.txt)

7. Routing Algorithms:
   * Distance Vector Routing (DVR): [Code](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Distance%20Vector%20Routing/DVR.c) & [Output](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Distance%20Vector%20Routing/outputDVR.txt)
   * Link State Routing (LSR): [Code](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Link%20State%20Routing/LSR.c) & [Output](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/Link%20State%20Routing/outputLSR.txt)
  
8. NS2:
   * Distance Vector Routing (DVR): [Code](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/NS2/distance-vector.tcl) & [Output](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/NS2/DVR%20-%20Output.png)
   * Link State Routing (LSR): [Code](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/NS2/link-state.tcl) & [Output](https://github.com/dyingpotato890/KTU-S6-CN-LAB/blob/main/NS2/LSR%20-%20Output.png) 

## Contributors:

1. [Niranjay Ajayan](https://github.com/dyingpotato890)
