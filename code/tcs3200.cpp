#include "hwlib.hpp"

int tcs3200::read(){//inbouwen van een failsafe!!! -----------------------------------------------------------------------------------------------------------------------------
    int i = 0;
    bool x = true, y = false, start = true;
    while(x){
        while(start){
            if(sensor_out.read() == false && y == false){
                y = true;
            }if(sensor_out.read() && y){
                start = false;
            }
        }
        //enter with a high state
        //y = true
        if(sensor_out.read() && y == false){
            x = false;
        }
        if(sensor_out.read() == false && y){
            y = false;
        }
        i++;
        hwlib::wait_us(1);
    }
    return i;
}