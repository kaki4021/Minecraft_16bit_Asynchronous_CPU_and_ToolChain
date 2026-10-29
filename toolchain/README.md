# **Custom Software Toolchain**
[How to Use?](code/README.md)  
마인크래프트 내의 16비트 비동기 CPU를 위해 밑바닥부터 자체 개발된 전용 툴체인입니다. 단순한 1:1 명령어 변환(Mnemonic to Opcode)을 넘어, 고수준 언어의 제어문과 디버깅 편의성을 제공합니다.

---
### **1.  Basic Structure**
코드는 기본적으로 `명령어(Opcode) 피연산자1(Operand1) 피연산자2(Operand2)` 형태를 띄며, 줄 단위로 파싱됩니다.
- **주석:**
`;` 뒤에 오는 내용은 무시됩니다.
- **라벨:**
`:LABEL_NAME` 을 사용하여 메모리 주소를 가리킬 수 있습니다. 이름 앞에 붙는 `:` 또한 라벨 이름에 포함됩니다.

---
### **2. Register**
사용 가능한 레지스터의 목록과 용도입니다.
- **`r1` ~ `r7`:**
범용 레지스터 (General Purpose Registers)
- **`bp`, `sp`:**
베이스 포인터 (Base Pointer), 스택 포인터 (Stack Pointer)
- **`pc`:**
프로그램 카운터 (Program Counter)
- **`in`, `out`:**
외부 입력값 (예: keyboard), 외부 출력값 (예: display)

---
### **3. Instruction Set**
#### **Exit Program**
- `exit`
---
#### **Data Movement**
| Opcode | Operands | Operation| Description  |
| --- | --- | --- | --- |
| `mov` | `reg1 reg2` | `reg1 = reg2` | **Copy (레지스터 복사):** `reg2`의 값을 `reg1`에 복사합니다. |
| `mov` | `reg1 [reg2]` | `reg1 = ram[reg2]` | **Load (메모리 읽기):** `reg2`가 가리키는 메모리 주소의 값을 `reg1`에 불러옵니다. |
| `mov` | `[reg1] reg2` | `ram[reg1] = reg2` | **Store (메모리 쓰기):** `reg2`의 값을 `reg1`이 가리키는 메모리 주소에 저장합니다. |
| `mov` | `reg1 [a+b]` | `reg1 = ram[a+b]` | **Load with Offset:** `a+b` 연산 결과 주소의 값을 `reg1`에 불러옵니다. |
| `mov` | `[a+b] reg2` | `ram[a+b] = reg2` | **Store with Offset:** `reg2`의 값을 `a+b` 연산 결과 주소에 저장합니다. |
| `mov` | `reg1 #c` | `reg1 = #c` | **Immediate (상수 로드):** 상수 값 `#c`를 `reg1`에 직접 대입합니다. |

**Notation Guide**  
- `[ ]`: 해당 레지스터의 값을 메모리 절대 주소로 취급하여 접근합니다(Dereference).  
- `[a+b]`: 주소 계산을 위한 오프셋 연산을 지원합니다. `a`와 `b`위치에는 레지스터, 상수, 라벨을 자유롭게 조합하여 넣을 수 있습니다. `+` 대신 `-` 연산자도 사용 가능합니다.   
(주의: 피연산자와 연산자 사이에는 공백이 없어야 합니다. 예: [r1+#5])
- `#`: 뒤에 오는 값을 순수 상수(Immediate Value)로 취급합니다.  
- `#b`: 뒤에 오는 값을 2진법 값으로 취급합니다.  
- `#`상수값 대신 `:LABEL_NAME` 또한 가능합니다. 
---
#### **Arithmetic & Logic**
| Opcode | Operands | Operation| Description  |
| --- | --- | --- | --- |
| `add` | `reg1 reg2` | `reg1 = reg1 + reg2` | **Add:** `reg1`과 `reg2`를 더합니다. |
| `sub` | `reg1 reg2` | `reg1 = reg1 - reg2` | **Subtract:** `reg1`에서 `reg2`를 뺍니다. |
| `or` | `reg1 reg2` | `reg1 = reg1 \| reg2` | **Bitwise OR:** 두 레지스터의 비트 단위 OR 연산을 수행합니다. |
| `and` | `reg1 reg2` | `reg1 = reg1 & reg2` | **Bitwise AND:** 두 레지스터의 비트 단위 AND 연산을 수행합니다. |
| `xor` | `reg1 reg2` | `reg1 = reg1 ^ reg2` | **Bitwise XOR:** 두 레지스터의 비트 단위 XOR 연산을 수행합니다. |
| `not` | `reg1` | `reg1 = ~reg1` | **Bitwise NOT:** `reg1`의 모든 비트를 반전시킵니다. |
| `inc` | `reg1` | `reg1 = reg1 + 1` | **Increment:** `reg1`의 값을 1 증가시킵니다. |
| `shl` | `reg1` | `reg1 = reg1 << 1` | **Shift Left:** `reg1`의 비트를 왼쪽으로 한 칸 이동합니다. |
| `shr` | `reg1` | `reg1 = reg1 >> 1` | **Shift Right:** `reg1`의 비트를 오른쪽으로 한 칸 이동합니다. |
| `rng` | `reg1` | `reg1 = (random number)` | **Random:** `reg1`의 값을 0부터 2^16-1 사이의 값중 랜덤한 값 하나로 변경합니다. |

**Secondary syntax**  
- `Operand2(reg2)` 자리에 `#c`(상수) 를 대신 넣는 것도 가능합니다. (예: `add r1 #123`)  
---
#### **Control Flow**
| Opcode | Operands | Operation | Description  |
| --- | --- | --- | --- |
| `jif` | `:LABEL_NAME` | `if (carry) pc = :LABEL_NAME` | **Jump If Carry:** `Carry Flag (CF)`의 값이 `1`인경우 지정된 라벨 주소로 점프합니다. |

**There is no `jmp` instruction**  
- `mov pc :LABEL_NAME` 을 대신 사용합니다.  

**Conditions for Setting the Carry Flag (CF)**  
- add/inc: 연산 결과 최상위 비트에서 자릿올림(Carry)이 발생할 때 1로 세팅됩니다. (덧셈 결과가 2^16-1을 초과할 경우)
- sub: 연산 결과 최상위 비트에서 자릿내림(Borrow)이 발생하지 않을 때 1로 세팅됩니다. (sub a b: a >= b 일 경우)
---
#### **Stack & Subroutines**
| Opcode | Operands | Operation | Description  |
| --- | --- | --- | --- |
| `push` | `reg1` | `sp = sp - 1`, `ram[sp] = reg1` | **Push**: `reg1`의 값을 스택에 저장하고 `sp`를 감소시킵니다. |
| `pop` | `reg1` | `reg1 = ram[sp]`, `sp = sp + 1` | **Pop**: 스택 최상단의 값을 `reg1`에 로드하고 `sp`를 증가시킵니다. |
| `call` | `:LABEL_NAME` | `push(return_address)`, `pc = :LABEL_NAME` | **Call**: 복귀 주소를 스택에 저장한 뒤 지정된 서브루틴 라벨로 점프합니다. |
| `ret` |  | `pop(pc)` | **Return**: 스택에서 복귀 주소를 복원하여 호출한 위치로 돌아갑니다. |

**Secondary syntax**  
- `push` 명령어의 `Operand` 자리에 `#c`(상수) 를 대신 넣는 것도 가능합니다. (예: `push #123`)  
---
#### **Input & Output**  
마인크래프트 인게임 하드웨어(디스플레이, 키보드)와 상호작용하기 위한 특수 명령어입니다. 별도의 피연산자 없이 `in`, `out` 레지스터를 암시적으로 사용합니다.
| Opcode | Description  |
| --- | --- |
| `dindex` | `out` 레지스터의 값을 디스플레이의 출력 인덱스로 지정합니다. |
| `dwrite` | `out` 레지스터의 값을 디스플레이에 출력합니다. |
| `iwait` | 키보드로부터 입력이 들어올 때 까지 대기합니다. 입력 키 값은 `in` 레지스터에 저장됩니다. |

**How to Use**  
Display Index:  
| | | | | | | | |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |  


```nasm
; 입력 대기 후, 입력받은 키를 디스플레이 3번 인덱스에 에코(Echo)
iwait
mov out #3
dindex       ; 디스플레이 인덱스를 3으로 설정
mov out in   ; 입력받은 값(in)을 출력 레지스터(out)로 복사
dwrite       ; 설정된 인덱스(3)에 값 출력
```

---


### **4. High-Level Control Structures**
#### **IF, ELIF, ELSE**  
조건을 만족할 때만 특정 블록을 실행합니다.  

```nasm
; 단순 if
if r1 < #10 ; 조건
    ; 조건이 참이면 실행될 코드
}
```
```nasm
; if-elif-else
if r1 == #1 ; 조건1
    ; 조건1이 참이면 실행될 코드
elif r2 == #2 ; 조건2
    ; 조건1이 거짓이고, 조건2가 참이면 실행될 코드
else
    ; 조건 1이 거짓이고, 조건2도 거짓이면 실행될 코드
}
```

**조건 작성법**  
- `a < b` 형태로 작성되며, `a`와 `b`자리에는 레지스터 이름 또는 상수(`#c`)가 들어갈 수 있습니다.
- 지원 연산자:  `==`, `!=`, `<`, `>`, `<=`, `>=` 입니다.
- 공백 규칙: 피연산자와 연산자 사이에는 반드시 스페이스 한 칸을 띄워야 합니다.

---
#### **WHILE**  
코드 블록을 반복 실행합니다. 조건은 작성 불가하며, 무한 반복입니다.  

```nasm
while
    inc r1 ; 무한 반복 실행될 코드
}
```

---
#### **FOR STEP**  
코드 블록을 반복 실행하되, 매 반복의 끝에 실행될 '증감(Step)' 로직을 별도로 분리하여 작성할 수 있는 특수 반복문입니다.  
C언어 `for`문의 증감식 부분과 동일한 역할을 수행하며, 루프 내에서 `continue`가 호출되더라도 `step` 구역의 코드는 스킵되지 않고 반드시 실행된 후 다음 반복으로 넘어갑니다. `while`문과 마찬가지로 기본적으로 무한 반복입니다.

```nasm
for
    add r1 r2 ; 무한 반복 실행될 코드
step
    inc r2 ; 마지막에 반드시 실행
}
```

---
#### **BREAK CONTINUE**  
루프(`while`, `for`)의 실행 흐름을 제어합니다. `break`는 반복문을 즉시 종료하고 탈출하며, `continue`는 현재 반복을 중단하고 다음 반복(또는 `step` 구역)으로 건너뜁니다.

```nasm
; r1이 0부터 시작하여 1씩 증가하다가 10이상이되면 반복 중단
xor r1 r1
while
    if r1 >= #10
        break
    }
    inc r1
}
```
```nasm
; 0부터 9까지중 5를 제외하고 더한값을 r2에 저장 (while 사용)
xor r1 r1
xor r2 r2
while
    if r1 >= #10
        break
    }
    if r1 == #5
        inc r1 ; continue로 인해 무한루프에 빠지지 않도록 수동 증감 필요
        continue ; while 블록의 처음으로 이동
    }
    add r2 r1
    inc r1
}
```
```nasm
; 0부터 9까지중 5를 제외하고 더한값을 r2에 저장 (for step 사용)
xor r1 r1
xor r2 r2
for
    if r1 >= #10
        break
    }
    if r1 == #5
        continue ; step 구역으로 이동
    }
    add r2 r1
step
    inc r1 ; 정상 종료 시점이나 continue 시점 모두 실행
}
```

---
#### **IFBREAK IFCONTINUE IFJMP (Branch Optimization)**  
일반적인 `if` 블록 내부에 제어 흐름 명령어(`break`, `continue`, `jmp`) 단 하나만 존재할 경우, 컴파일러 구조상 조건을 우회하기 위한 불필요한 분기(Jump) 오버헤드가 발생합니다. 이를 어셈블리 레벨에서 1개의 `jif` 명령어로 최적화(인라인 점프)하기 위해 제공되는 고급 명령어입니다. `ifbreak`, `ifcontinue`, `ifjmp`


```nasm
; if r1 < r2
; 	break
; }

; 컴파일 결과: 불필요한 분기 명령(mov pc)이 추가로 발생
mov tmp1 r1
sub tmp1 r2
jif ::if0_0
mov pc ::while0_e
::if0_0

... 라벨 생략 ...
```
```nasm
; ifbreak r1 <= r2

; 컴파일 결과: 단일 jif 명령어로 최적화
mov tmp1 r2
sub tmp1 r1
jif ::while0_e
```

**사용 규칙**
- 기본적인 조건 작성법은 `if`문과 동일하지만, 단일 라인 명령이므로 중괄호 `}`로 블록 구역을 닫지 않습니다.  
- `ifjmp`의 경우 점프할 타겟 라벨을 함께 명시해야 합니다. (예: `ifjmp r1 == #10 :TARGET_LABEL`)

---
#### **DEFINE**  
단순 텍스트 치환 전처리 입니다.  
`define A B`  
A를 B로 치환하여 컴파일 합니다. 
```nasm
define I r1
mov I I
mov I [I]
mov [I] I
```
위 컴파일 시 아래의 결과
```nasm
mov r1 r1
mov r1 [r1]
mov [r1] r1
```

---
### **5. Memory & Data Allocation**
컴파일 타임에 정적 데이터, 배열, 문자열 등을 메모리에 할당하고 초기화하기 위해 `.data`와 `./data` 지시어 구역을 사용합니다.

```nasm
.data
:ARR
0
1
2
3
4
5
:I
0
:CHAR
'K'
:STR
"HELLO WORLD"
./data
```
**데이터 선언 규칙**  
- **구역 설정:**
데이터 선언부는 반드시 `.data`로 시작하여 `./data`로 닫아야 합니다. 코드 내 위치는 상관없으며 2개 이상의 구역을 만들 수 있습니다.
- **라벨 주소 바인딩:**
`:LABEL_NAME` 을 선언하면, 그 아래에 나열되는 데이터들의 시작 메모리 주소가 해당 라벨에 바인딩됩니다. 코드 영역에서 `mov r1 :ARR`와 같이 작성하여 해당 데이터 배열의 시작 주소를 레지스터로 불러올 수 있습니다.
- **지원 데이터 형식:**
  - **정수 배열:** 한 줄에 하나의 숫자 값을 입력하여 메모리에 순차적으로 할당합니다.
  - **문자 (Character):** 'K'와 같이 작은따옴표를 사용하여 단일 문자의 숫자 코드값을 할당합니다.
  - **문자열 (String):** `"HELLO WORLD"`와 같이 큰따옴표를 사용하여 문자열을 선언하면, 컴파일러가 각 문자를 메모리에 연속된 형태로 자동 분할하여 할당합니다. 배열의 마지막에는 `'\0'`(NULL)을 자동 할당합니다.


---
### **6. Error Tracking & Debugging**
컴파일 과정에서 문법 오류나 잘못된 참조가 발생할 경우, 컴파일러는 단순히 작동을 멈추는 것에 그치지 않고 오류가 발생한 구체적인 원인과 라인번호 그리고 해당 코드의 주변 컨텍스트를 시각적으로 출력하려 빠른 디버깅을 돕습니다.

**1) Register Name Error**  
존재하지 않는 레지스터(예: `r0` 등)에 접근하려고 할 때 발생합니다.

```nasm
r0: register name error
3 while
4 ifbreak r1 >= #10
5 add r2 r0    <- HERE
6 inc r1
7 }
```

**2) Symbol Not Found**  
선언되지 않은 라벨 사용을 시도했을 때 발생합니다.

```nasm
:fun: symbol not found
3 while
4 ifbreak r1 >= #10
5 call :fun    <- HERE
6 inc r1
7 }
```

**3) Command Type Error**  
사전에 정의되지 않은 명령어(예: `mov`를 `move`로 잘못 작성)를 입력했을 때 발생합니다.

```nasm
move: command type error
3 while
4 ifbreak r1 >= #10
5 move r2 r1    <- HERE
6 inc r1
7 }
```

**4) General Syntax Error**  
피연산자(Operand)의 개수가 부족하거나, 기타 예측할 수 없는 문법적 오류가 발생했을 때 출력됩니다.

```nasm
SOMETHING ERROR...
3 while
4 ifbreak r1 >= #10
5 xor r1    <- HERE
6 inc r1
7 }
```

