#include "encoder.h"

Encoder::Encoder(TIM_HandleTypeDef* htim, uint32_t cpr) : htim_(htim), cpr_(cpr) {}

void Encoder::enable(){
	HAL_TIM_Encoder_Start(htim_, TIM_CHANNEL_ALL);

}

float Encoder::getAngle() const{
	return getCount() * 360.0f / cpr_;


}

void Encoder::setAngle(float degrees) {
	__HAL_TIM_SET_COUNTER(htim_, (uint32_t)(int32_t)(cpr_* degrees/360.0f));
}

int32_t Encoder::getCount() const{
	return (int32_t)__HAL_TIM_GET_COUNTER(htim_);
}
