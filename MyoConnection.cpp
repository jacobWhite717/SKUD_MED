#include "MyoConnection.h"
#include "Arduino.h"

MyoConnection::MyoConnection(int rx_pin, int tx_pin) :
    _serial_connection(SoftwareSerial(rx_pin, tx_pin)),
    _myo_connection(this->_serial_connection)
{
}

void MyoConnection::init() {
    Serial.begin(115200);
    _serial_connection.begin(115200);
    _myo_connection.begin();
    _myo_connection.setPoseEventCallBack(handle_pose_data);
    _myo_connection.enablePoseData();
    _myo_connection.unlockMyo();
}

void MyoConnection::handle_pose_data(MyoPoseData& data) {
    MyoPose pose;
    pose = (MyoPose)data.pose;
    myo_buffer = pose;
}

MyoConnection::Poses MyoConnection::update_pose() {
    this->_myo_connection.update();
    this->_pose = string_to_pose(this->_myo_connection.poseToString(myo_buffer));
    return this->_pose;
}

MyoConnection::Poses MyoConnection::string_to_pose(String pose) {
    if(pose == "MYO_POSE_REST") {
        return MyoConnection::Poses::rest;
    } 
    else if(pose == "MYO_POSE_FIST") {
        return MyoConnection::Poses::fist;
    } 
    else if(pose == "MYO_POSE_DOUBLE_TAP") {
        return MyoConnection::Poses::double_tap;
    } 
    else if(pose == "MYO_POSE_WAVE_OUT") {
        return MyoConnection::Poses::wave_out;
    } 
    else if(pose == "MYO_POSE_WAVE_IN") {
        return MyoConnection::Poses::wave_in;
    } 
    // FIXME: make sure that this is the correct string
    else if(pose == "MYO_POSE_FINGERS_SPREAD") {
        return MyoConnection::Poses::fingers_spread;
    }
    else {
        return MyoConnection::Poses::bad_pose;
    }
}
