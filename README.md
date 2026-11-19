# ME5305 Ping Pong Turret Project

Group project for ME5305, Mechatronics 3. A custom-designed turret that aims and launches ping-pong balls at different angles and speeds. A yaw motor with an encoder aims the turret, three BLDC flywheel motors launch the ball, and a servo feeds the balls into the flywheels. The firmware runs on a custom designed PCB with an STM32F411CEU6 MCU. 

### Contributors: Micheal Duperly, Eric Lee

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
| TIM3 | ESC PWM | PB4, PB5, PB0, PB1 | 
| TIM4 | Yaw PWM | PB8, PB9 |

## Firmware Class
| Class | File | Function |
| :---: | :--: | :------: | 
| yawmotor | yawmotor.h/cpp | PWM driver for yaw motor: enable, disable, set duty cycle |
| Encoder | encoder.h/cpp | Read encoder count and convert it to an angle using CPR |
| BLDCMotor | BLDCMotor.h/cpp | Arm ESC and set throttle as a percentage or raw pulse width |
| Servo | Servo.h/cpp | Command an angle into a 50 Hz pulse |
| LimitSwitch | limit_switch.h | Read activation, reset | 

## Flashing 
1. Clone the repo
2. File -> Import -> Existing projects into workspace -> select Term_Project folder
3. Project -> Build Project

Download CubeIDE and CubeMX to modify the code and pins.






