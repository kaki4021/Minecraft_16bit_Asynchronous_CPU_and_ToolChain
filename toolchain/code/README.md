개발/테스트 OS: Windows 11 (23H2)

사용법:  
./input.txt 파일에 컴파일 할 코드를 넣고 실행 시 정상적으로 컴파일되면 .mcfunction에 넣을 내용이 클립보드에 복사됨. 해당 .mcfunction 내용을 실행 시 램에 자동으로 프로그램이 올라가게 됨.

---
```asm
:scan_dec ; i(r1 print_index) o(r2) c(r3)
	xor r2 r2
	while
		iwait
		ifbreak in == #'\n'

		mov out r1
		dindex
		mov out in
		dwrite
		inc r1

		shl r2
		mov r3 r2
		shl r2
		shl r2
		add r2 r3

		add r2 in
	}
ret
```
컴파일 시 아래 내용이 클립보드에 복사됨.
```
setblock 33 87 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 85 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 83 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 81 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 79 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 77 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = true]
setblock 33 75 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = true]
setblock 33 73 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 69 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 67 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 65 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 63 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 61 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 59 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = true]
setblock 33 57 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 33 55 94 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]

... 생략 ...

setblock 41 87 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 85 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 83 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 81 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 79 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 77 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 75 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 73 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 69 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 67 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 65 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 63 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 61 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 59 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 57 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]
setblock 41 55 127 minecraft:repeater[facing = west, locked = true, delay = 1, powered = false]


tellraw @a {"text":"program loaded"}
```
