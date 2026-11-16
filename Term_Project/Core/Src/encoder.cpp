#include "encoder_class.h"

Encoder::Encoder(int pinA, int pinB) {}

void Encoder::enable(){

}

void Encoder::disable(){

}

void Encoder::update(){

}



void Encoder::getPosition() const {return position_;}
void Encoder::setPosition(float pos) {position_ = pos;}
void Encoder::reset() {position_ = 0}
