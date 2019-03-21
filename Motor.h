#ifndef MOTOR_H
#define MOTOR_H


class Motor {
    public:
        Motor(int speed_pin, int out_pin, int in_pin);
        void init();

        void in(int speed = 255);
        void out(int speed = 255);
        void stop();
    
    private:
        int _speed_pin;
        int _in_pin;
        int _out_pin;
};

#endif // MOTOR_H