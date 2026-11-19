// Lab 9 software-only check: runs the real driver .cpp files against a mock timer.
// Build: g++ -std=c++17 -Imock -I../Term_Project/Core/Inc sw_check.cpp ../Term_Project/Core/Src/{encoder,Servo,BLDCMotor,yawmotor,limit_switch}.cpp
#include <cstdio>
#include <cmath>
#include "encoder.h"
#include "Servo.h"
#include "BLDCMotor.h"
#include "yawmotor.h"
#include "limit_switch.h"
uint32_t mock_tick = 0; GPIO_PinState mock_pin = GPIO_PIN_SET;
static int fails = 0, n = 0;
static void chk(const char* name, double expected, double actual, double tol = 1e-3){
  bool ok = std::fabs(expected - actual) <= tol; n++; if(!ok) fails++;
  std::printf("%-46s expected %10.3f  actual %10.3f  %s\n", name, expected, actual, ok ? "PASS" : "FAIL");
}
int main(){
  TIM_HandleTypeDef t2{}, t1{}, t3{}, t4{};
  std::puts("-- Encoder (TIM2, 32-bit, cpr = 4000 example) --");
  Encoder enc(&t2, 4000); enc.enable();
  t2.cnt = 1000;                 chk("1000 counts -> deg", 90.0, enc.getAngle());
  t2.cnt = 4000;                 chk("4000 counts -> deg", 360.0, enc.getAngle());
  t2.cnt = (uint32_t)(-500);     chk("-500 counts (underflow) -> deg", -45.0, enc.getAngle());
  enc.setAngle(45.0f);           chk("setAngle(45) -> counter", 500, (int32_t)t2.cnt);
  enc.setAngle(-45.0f);          chk("setAngle(-45) -> counter", -500, (int32_t)t2.cnt);
  chk("cpr = 0 guard -> deg", 0.0, Encoder::countsToDegrees(100, 0));
  std::puts("-- Servo (TIM1 CH1, 1 us tick) --");
  Servo s(&t1, TIM_CHANNEL_1, 0, 180); s.start();
  chk("start() -> CCR1 (gate closed)", 1000, t1.ccr[0]);
  s.write(90);                   chk("write(90) -> CCR1 us", 1500, t1.ccr[0]);
  s.write(180);                  chk("write(180) -> CCR1 us", 2000, t1.ccr[0]);
  s.write(250);                  chk("write(250) clamps -> CCR1 us", 2000, t1.ccr[0]);
  std::puts("-- BLDC/ESC (TIM3 CH1, 1 us tick) --");
  BLDCMotor esc(&t3, TIM_CHANNEL_1); esc.start();
  chk("start() -> CCR1 us (min throttle)", 1000, t3.ccr[0]);
  esc.arm(); mock_tick = 500;    esc.setThrottle(50);
  chk("throttle 50% before armed -> us", 1000, t3.ccr[0]);
  mock_tick = 2000;              esc.setThrottle(50);
  chk("throttle 50% after 2 s arm -> us", 1500, t3.ccr[0]);
  esc.setThrottle(150);          chk("throttle 150% clamps -> us", 2000, t3.ccr[0]);
  esc.stop();                    chk("stop() -> us", 1000, t3.ccr[0]);
  std::puts("-- Yaw motor (TIM4 CH3/CH4, ARR = 4799 -> 20 kHz) --");
  t4.arr = 4799; yawmotor yaw(&t4, TIM_CHANNEL_3, TIM_CHANNEL_4); yaw.init(); yaw.Motor_Enable();
  yaw.Motor_SetDutyCycle(50);    chk("+50% -> IN1 CCR3", 2400, t4.ccr[2]); chk("+50% -> IN2 CCR4", 0, t4.ccr[3]);
  yaw.Motor_SetDutyCycle(-25);   chk("-25% -> IN1 CCR3", 0, t4.ccr[2]);    chk("-25% -> IN2 CCR4", 1200, t4.ccr[3]);
  yaw.Motor_SetDutyCycle(127);   chk("+127% clamps -> IN1 CCR3", 4800, t4.ccr[2]);
  yaw.Motor_Disable();           chk("disable -> IN1 CCR3", 0, t4.ccr[2]); chk("disable -> PWM off", 0, t4.pwm_on[2]);
  std::puts("-- Limit switch (active low) --");
  LimitSwitch lim(nullptr, 0); mock_pin = GPIO_PIN_SET; lim.read(); chk("pin high -> pressed", 0, lim.get());
  mock_pin = GPIO_PIN_RESET; lim.read(); chk("pin low -> pressed", 1, lim.get());
  std::printf("\n%d/%d checks passed\n", n - fails, n);
  return fails ? 1 : 0;
}
