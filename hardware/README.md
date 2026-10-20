# **Hardware Architecture**

마인크래프트 내의 16비트 비동기 CPU 입니다.
아래는 ISA 명세서 입니다.  

---  
| Command | Opcode | Micro Commands | Operands / Note |
| :--- | :--- | :--- | :--- |
| exit | _00000 | | |
| mov r1 r2 | _00001 | DSR on, mov r1 r2, ;;DSR off | dst(r1), src(r2) |
| mov r1 [r2] | _00010 | (SR on, dst mar on, mov r1 r2, SR off, dst mar off)(SDMSD), load, DR on, write, ;;DR off | dst(r1), src(r2) |
| mov [r1] r2 | _00011 | (SR on, dst mar on, mov r1 r2, SR off, dst mar off)(SDMSD), D to S on, DR on, save, ;;read off, ;;DR off | dst(r2), src(r1); reverse! |
| mov r1 #c | _00100 | fetch2, DR on, write, ;;DR off | dst(r1) |
| add r1 r2 | _00101 | add, (D to S on, DSR on, read on, alu1, read off, D to S off, read on, alu2, alu on), write, alu off | dst(r1), src(r2) |
| sub r1 r2 | _00110 | sub, Double alu, write, alu off | |
| inc r1 | _00111 | inc, write, alu off | |
| not r1 | _01000 | not, (DSR on, read on, alu1, alu on), write, alu off | dst(r1), src(r1) |
| or r1 r2 | _01001 | | |
| and r1 r2 | _01010 | or | |
| xor r1 r2 | _01011 | xor | |
| shl r1 | _01100 | shl | |
| shr r1 | _01101 | shr | |
| jif (no jmp) | _01111 | fetch2, fetch | |
| jif (do mp) | _01111 | fetch2, mov r1 #c | dst(pc) |
| rng r1 | _10000 | DR on, rng on, wrtie, rng off | dst(r1) |
| iwait | _11100 | | |
| dreset | _11101 | | |
| dindex | _11110 | | |
| dwrite | _11111 | | |
  
`(3) + dst(4) + src(4) + opcode(5)`

---
| Micro Command | Opcode | Ack Type |
| :--- | :--- | :--- |
| | _00000 | |
| fetch | _00001 | |
| move r1 r2 | _00010 | write |
| fetch2 | _00011 | ram |
| save | _00100 | ram |
| load | _00101 | ram |
| SR on | _00110 | n |
| SR off | _00111 | n |
| DR on | _01000 | n |
| DR off | _01001 | n |
| DSR on | _01010 | n |
| DSR off | _01011 | n |
| read on | _01100 | read |
| read off | _01101 | n |
| write | _01110 | write |
| SDMSD | _01111 | write |
| D to S on | _10000 | n |
| D to S off | _10001 | n |
| Single alu | _10010 | alu |
| Double alu | _10011 | alu |
| alu off | _10100 | n |
| inc | _10101 | alu |
| rng on | _10110 | n |
| rng off | _10111 | n |

---
| Register Name | Address | Access |
| :--- | :--- | :--- |
| tmp1 | _0000 | |
| tmp2 | _0001 | |
| bp | _0010 | |
| sp | _0011 | |
| pc | _0100 | |
| tmp3 | _0101 | |
| input_key | _0110 | cpu read only |
| mar | _0111 | cpu write only, ram read only |
| r1 | _1000 | |
| r2 | _1001 | |
| r3 | _1010 | |
| r4 | _1011 | |
| r5 | _1100 | |
| r6 | _1101 | |
| r7 | _1110 | |
| out | _1111 | |
