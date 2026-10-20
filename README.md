# Minecraft 16-bit Asynchronous CPU & ToolChain

단순한 마인크래프트 레드스톤 장난감을 넘어, 실제 컴퓨터 공학 이론에 기반한 완전한 16비트 비동기 연산 시스템과 소프트웨어 입니다. 하드웨어 아키텍처 설계부터 전용 어셈블러 개발까지 풀스택으로 자체 제작하여, 복잡한 재귀 알고리즘과 수식 처리 과정을 클럭(Clock)의 제약 없이 완벽하게 수행할 수 있음을 증명합니다.

### 1.  [Hardware Architecture](hardware/README.md)
- **Asynchronous (Clockless) Architecture:**  
클럭 펄스 대신 비동기 핸드셰이크(Req/Ack) 신호 기반으로 동작하여 병목을 최소화합니다.
- **Microcoded Control Unit:**  
ROM 기반 마이크로코드 채택으로 유연한 ISA 확장 가능합니다.
- **Custom ISA (Instruction Set Architecture):**  
산술 연산, 스택제어, 분기 등을 포함한 독자적인 명령어 셋을 설계했습니다.

### 2. [Custom Software Toolchain](toolchain/README.md)
- **High-Level Assembly Compiler:**  
매크로, 라벨링, 전처리기, while/if 등 을 지원하는 자체 제작 컴파일러로, 복잡한 어셈블리 코드를 마인크래프트 메모리(RAM) 규격에 맞게 완벽히 변환합니다.
- **Error Tracking & Debugging Support:**  
개발 편의성을 위해 컴파일러 내에 오류 추적 시스템을 구축했습니다. 문법 오류나 잘못된 명령어 입력 등으로 컴파일 에러 발생 시, 오류가 발생한 정확한 코드 라인 번호(Line Number)를 출력하여 디버깅 시간을 획기적으로 단축해 줍니다.
