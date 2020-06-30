#include "hwlib.hpp"
#include "rail_switch.hpp"
#include "tcs3200.hpp"
//#include "tcs3200.cpp"
#include "tcs3200_switch.hpp"

int main( void ){
    auto s0 = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto s1 = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto s2 = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto s3 = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto sensor_out = hwlib::target::pin_in(hwlib::target::pins::d8);

    auto chip = tcs3200(s0,s1,s2,s3,sensor_out);
    
    //auto led0 = hwlib::target::pin_out(hwlib::target::pins::d22);

    auto pin0 = hwlib::target::pin_out(hwlib::target::pins::d23);
    auto pin1 = hwlib::target::pin_out(hwlib::target::pins::d24);

    auto switch0 = rail_switch(pin0,pin1);

    rgb wagon = chip.read_rgb();

    auto x = tcs3200_switch(chip,switch0,wagon);
    x.start();
}


