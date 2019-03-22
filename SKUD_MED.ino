#include "MyoHand.h"

// Analog inputs for FSRs
const int THUMB_FSR_PIN  = A1;
const int INDEX_FSR_PIN = A2;
const int MIDDLE_FSR_PIN = A3;
const int RING_FSR_PIN = A4;
const int PINKY_FSR_PIN = A5;

// class objects
Motor wrist_motor(11, 13, 12);
Motor pinch_motor(10, 8, 7);
Motor grasp_motor(9, 6, 5);
MyoConnection bluetooth(2, 3);
MyoHand hand(wrist_motor, pinch_motor, grasp_motor, bluetooth, 
            THUMB_FSR_PIN, INDEX_FSR_PIN, MIDDLE_FSR_PIN, 
            RING_FSR_PIN, PINKY_FSR_PIN);


void setup() {
    hand.init();
}


void loop() {
    hand.update_hand();
}

// TODO:
// note to self - make 3 more fields in hand that are the speeds for each Motor
// make a new function called updated speeds
// this function will check all fsr's readings and control the speed vars accordinly 
// add a call to this new function before every motor movement helper function 