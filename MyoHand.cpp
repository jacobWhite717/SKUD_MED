#include "MyoHand.h"
#include "Arduino.h"

MyoHand::MyoHand(Motor& wrist_mot, Motor& pinch_mot, Motor& grasp_mot, MyoConnection& connection, 
                int thumb, int index, int middle, int ring, int pinky) :
    _wrist_motor(wrist_mot),
    _pinch_motor(pinch_mot),
    _grasp_motor(grasp_mot),
    _connection(connection),
    _thumb_fsr_pin(thumb),
    _index_fsr_pin(index),
    _middle_fsr_pin(middle),
    _ring_fsr_pin(ring),
    _pinky_fsr_pin(pinky)
{
}

void MyoHand::init() {
    pinMode(this->_thumb_fsr_pin, INPUT);
    pinMode(this->_index_fsr_pin, INPUT);
    pinMode(this->_middle_fsr_pin, INPUT);
    pinMode(this->_ring_fsr_pin, INPUT);
    pinMode(this->_pinky_fsr_pin, INPUT);

    this->_wrist_motor.init();
    this->_pinch_motor.init();
    this->_grasp_motor.init();

    this->_connection.init();
}

void MyoHand::update_hand() {
    this->update_pose();

    switch (this->_current_pose) {
        case MyoConnection::Poses::rest:
            this->rest();
            break;
        case MyoConnection::Poses::fist:
            this->fist();
            break;
        case MyoConnection::Poses::wave_in:
            this->wave_in();
            break;
        case MyoConnection::Poses::wave_out:
            this->wave_out();
            break;
        case MyoConnection::Poses::double_tap:
            this->double_tap();
            break;
        case MyoConnection::Poses::fingers_spread:
            this->finger_spread();
            break;
        default:
            break;
    }
}

void MyoHand::update_pose() {
    this->_current_pose = this->_connection.update_pose();
}

// TODO: something with this
void MyoHand::read_FSRs() {
    this->_thumb_force = analogRead(this->_thumb_fsr_pin);
    this->_index_force = analogRead(this->_index_fsr_pin);
    this->_middle_force = analogRead(this->_middle_fsr_pin);
    this->_ring_force = analogRead(this->_ring_fsr_pin);
    this->_pinky_force = analogRead(this->_pinky_fsr_pin);
}

void MyoHand::stop_motors() {
    this->_wrist_motor.stop();
    this->_pinch_motor.stop();
    this->_grasp_motor.stop();
}

void MyoHand::rest() {
    this->stop_motors();
    delay(10);
    this->_last_pose = MyoConnection::Poses::rest;
}

void MyoHand::fist() {
    this->stop_motors();
    this->_grasp_motor.in();
    this->_pinch_motor.in();
    delay(10);
    this->stop_motors();
    
    this->_last_pose = MyoConnection::Poses::fist;
}

void MyoHand::wave_in() {
    this->stop_motors();
    this->_wrist_motor.in();
    delay(10);
    this->stop_motors();
    
    this->_last_pose = MyoConnection::Poses::wave_in;
}

void MyoHand::wave_out() {
    this->stop_motors();
    this->_wrist_motor.out();
    delay(10);
    this->stop_motors();
    
    this->_last_pose = MyoConnection::Poses::wave_out;
}

// TODO: figure out - currnetly just does a pinch
void MyoHand::double_tap() {
    this->stop_motors();
    this->_pinch_motor.in();
    delay(10);
    this->stop_motors();
    
    this->_last_pose = MyoConnection::Poses::double_tap;
}

void MyoHand::finger_spread() {
    this->stop_motors();
    this->_pinch_motor.out();
    this->_grasp_motor.out();
    delay(10);
    this->stop_motors();
    
    this->_last_pose = MyoConnection::Poses::fingers_spread;
}
