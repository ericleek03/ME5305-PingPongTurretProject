#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f4xx_hal.h"
class Encoder {
    public:
        Encoder(TIM_HandleTypeDef* htim, uint32_t cpr);
        void enable();

        float getAngle() const;
        void setAngle(float degrees);
        int32_t getCount() const;

    private:
      TIM_HandleTypeDef* htim_;
      uint32_t cpr_;
      float angle_;

};
#endif
