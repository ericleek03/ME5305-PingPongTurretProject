#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f4xx_hal.h"

// Quadrature encoder on a 32-bit timer (TIM2) in encoder mode, x4 decoding.
// cpr = counts per revolution of the shaft being measured (after x4 decoding
// and any gear reduction). Value for the PG6712A077 output shaft is provisional.
class Encoder {
    public:
        Encoder(TIM_HandleTypeDef* htim, uint32_t cpr);
        void enable();

        float getAngle() const;          // degrees, signed, relative to last setAngle()
        void setAngle(float degrees);    // used when the limit switch is reached (homing)
        int32_t getCount() const;

        static float countsToDegrees(int32_t counts, uint32_t cpr);

    private:
      TIM_HandleTypeDef* htim_;
      uint32_t cpr_;
};
#endif
