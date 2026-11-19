#include "encoder.h"

Encoder::Encoder(TIM_HandleTypeDef* htim, uint32_t cpr) : htim_(htim), cpr_(cpr) {}

void Encoder::enable(){
	__HAL_TIM_SET_COUNTER(htim_, 0);
	HAL_TIM_Encoder_Start(htim_, TIM_CHANNEL_ALL);
}

// The TIM2 counter is 32 bits; reading it as int32_t gives a signed position,
// so reverse motion past zero reads as negative counts instead of ~4e9.
float Encoder::countsToDegrees(int32_t counts, uint32_t cpr){
	if (cpr == 0) {return 0.0f;}
	return (float)counts * 360.0f / (float)cpr;
}

float Encoder::getAngle() const{
	return countsToDegrees(getCount(), cpr_);
}

void Encoder::setAngle(float degrees) {
	int32_t counts = (int32_t)((float)cpr_ * degrees / 360.0f);
	__HAL_TIM_SET_COUNTER(htim_, (uint32_t)counts);
}

int32_t Encoder::getCount() const{
	return (int32_t)__HAL_TIM_GET_COUNTER(htim_);
}
