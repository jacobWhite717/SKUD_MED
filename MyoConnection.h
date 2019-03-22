
#ifndef MYOCONNECTION_H
#define MYOCONNECTION_H


#include <MyoBridge.h>
#include "SoftwareSerial.h"

static MyoPose myo_buffer; 

class MyoConnection {
    public:
        enum class Poses {
            rest,
            fist,
            double_tap,
            wave_out,
            wave_in,
            fingers_spread,
            bad_pose
        };

        MyoConnection(int rx_pin, int tx_pin);
        void init();

        static void handle_pose_data(MyoPoseData& data);
        MyoConnection::Poses update_pose();

    private: // helper functions
        MyoConnection::Poses string_to_pose(String pose);

    private:
        MyoConnection::Poses _pose;
        SoftwareSerial _serial_connection;
        MyoBridge _myo_connection;
};

#endif // MYOCONNECTION_H
