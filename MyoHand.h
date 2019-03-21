#ifndef MYOHAND_H
#define MYOHAND_H


#include "Motor.h"
#include "MyoConnection.h"

class MyoHand {
    public:
        MyoHand(Motor wrist_mot, Motor pinch_mot, Motor grasp_mot, MyoConnection connection, 
                int thumb, int index, int middle, int ring, int pinky);
        void init();

        void update_hand();

    private: // helpers
        void update_pose(); 
        void read_FSRs();
        void stop_motors();

        void rest();
        void fist();
        void wave_in();
        void wave_out();
        void double_tap();
        void finger_spread();

    private:
        // BTLE connection to Myo armband
        MyoConnection _connection;

        // Motor control logic
        Motor _wrist_motor;
        Motor _pinch_motor;
        Motor _grasp_motor;
        
        // fsr pins / read val vars
        int _thumb_fsr_pin;
        int _index_fsr_pin;
        int _middle_fsr_pin;
        int _ring_fsr_pin;
        int _pinky_fsr_pin;
        int _thumb_force;
        int _index_force;
        int _middle_force;
        int _ring_force;
        int _pinky_force;

        // control how motors operate based on last pose / current pose
        MyoConnection::Poses _current_pose;
        MyoConnection::Poses _last_pose;
};

#endif // MYOHAND_H