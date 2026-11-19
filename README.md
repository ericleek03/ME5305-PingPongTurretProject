# ME5305 Ping Pong Turret Project

Group project for ME5305, Mechatronics 3. A custom-designed turret that aims and launches ping-pong balls at different angles and speeds. A yaw motor with an encoder aims the turret, three BLDC flywheel motors launch the ball, and a servo feeds the balls into the flywheels. The firmware runs on a custom designed PCB with an STM32F411CEU6 MCU. 

### Contributors: Michael Duperly, Eric Lee

## Repository Layout
```text
Term_Project/
├── Term_Project.ioc/       # CubeMX configuration
├── Core/                   # Main source code
│   ├── Inc/                # Headers for driver classes
│   └── Src/                # Driver implementation & main file
├── Drivers/                # STM32 HAL / CMSIS
├── .gitignore              # Ignored files and build artifacts
├── STM32F411CEUX_FLASH.ld  # Scripts
└── STM32F411CEUX_RAM.ld    # Scripts
```
## Hardware
| Task | Item | 
| :--: | :--: | 
|  MCU | STM32F411CEU6 | 
| Yaw Axis | Pittman PG6712A077-R3 Motor |
| Launcher |  RS2205 2300KV BLDC Motor |
| Feeder | SG90 Servo |
| Calibration | Limit Switch |
| Sensor | SEN05003 IR Break Beam | 

Timers
| Timer | Task | Pins | 
| :---: | :--: | :--: |
| TIM1 | Servo PWM (50 Hz) | PA8|
| TIM2 | Yaw Encoder (encoder mode) | PA15, PB3 |
| TIM3 | ESC PWM (CH1-CH3) | PB4, PB5, PB0 | 
| TIM4 | Yaw PWM | PB8, PB9 |

## Firmware Class
| Class | File | Function |
| :---: | :--: | :------: | 
| yawmotor | yawmotor.h/cpp | PWM driver for yaw motor: enable, disable, set duty cycle |
| Encoder | encoder.h/cpp | Read encoder count and convert it to an angle using CPR |
| BLDCMotor | BLDCMotor.h/cpp | Arm ESC and set throttle as a percentage or raw pulse width |
| Servo | Servo.h/cpp | Command an angle into a 50 Hz pulse |
| LimitSwitch | limit_switch.h/cpp | Read active-low switch state, EXTI hook | 

## Revision
- Board: Rev 1F (schematic 11/07/2026), ordered from JLCPCB
- Firmware: branch `lab9-michael`, update date 11/18/2026 (Lab 9 submission), based on `main` @ 8328e4b

## Target and Toolchain
- MCU: STM32F411CEU6, 8 MHz HSE, SYSCLK 96 MHz
- STM32CubeIDE (GNU Arm Embedded GCC), STM32Cube FW_F4 V1.28.3 HAL
- C for CubeMX-generated code (`main.c`), C++ for driver classes

## Build
1. Clone the repo to a path **without `#`** (make treats `#` as a comment), e.g. `C:\Users\<you>\STM32CubeIDE\workspace\`
2. CubeIDE: File -> Import -> Existing Projects into Workspace -> select `Term_Project` (do not copy)
3. Project -> Clean, then Project -> Build Project

Download CubeIDE and CubeMX to modify the code and pins.

## Software Check (runs on a PC, no hardware)
`SoftwareCheck/sw_check.cpp` compiles the real driver sources against a small stand-in HAL (`SoftwareCheck/mock/stm32f4xx_hal.h`) and compares register values with hand-calculated values.
```
cd SoftwareCheck
g++ -std=c++17 -Imock -I../Term_Project/Core/Inc sw_check.cpp ../Term_Project/Core/Src/encoder.cpp ../Term_Project/Core/Src/Servo.cpp ../Term_Project/Core/Src/BLDCMotor.cpp ../Term_Project/Core/Src/yawmotor.cpp ../Term_Project/Core/Src/limit_switch.cpp -o sw_check
./sw_check
```
Last result: 24/24 checks passed (`sw_check_output.txt`). This checks driver math only, not hardware behavior.

## Unfinished Functionality
- CubeMX changes still needed to match Rev 1F: PA1 -> ADC1_IN1, PA2/PA3 limit-switch inputs, PB1 -> LED GPIO, remove TIM4 CH1/CH2 (PB6/PB7), TIM1 CH1 -> PWM, TIM1/TIM3 PSC 95 ARR 19999 (50 Hz), TIM4 PSC 0 ARR 4799 (20 kHz), encoder CS initial level High
- Drivers not written yet: IR beam sensor (`triggerinput.h` placeholder), AS5047P SPI encoders, VIN/E-stop analog sense, UART command parser
- Task state machines (supervisor, yaw, flywheel, feed) are designed but not coded in `main.c`
- Provisional values: yaw encoder CPR, ESC and servo pulse ranges, ESC arming time, homing timeout
- No driver has been tested on hardware yet (Lab 10)
