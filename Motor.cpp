#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int speed_pin, int out_pin, int in_pin) : 
    _speed_pin(speed_pin),
    _in_pin(in_pin),
    _out_pin(out_pin)
{
}

void Motor::init() {
    pinMode(this->_speed_pin, OUTPUT);
    pinMode(this->_in_pin, OUTPUT);
    pinMode(this->_out_pin, OUTPUT);
}

void Motor::in(int speed) {
    analogWrite(this->_speed_pin, speed);
    digitalWrite(this->_in_pin, HIGH);
    digitalWrite(this->_out_pin, LOW);
}

void Motor::out(int speed) {
    analogWrite(this->_speed_pin, speed);
    digitalWrite(this->_in_pin, LOW);
    digitalWrite(this->_out_pin, HIGH);
}

void Motor::stop() {
    analogWrite(this->_speed_pin, 0);
    digitalWrite(this->_in_pin, LOW);
    digitalWrite(this->_out_pin, LOW);
}