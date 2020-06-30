#include "hwlib.hpp"
#include "rail_switch.hpp"
#include "tcs3200.hpp"
//#include "tcs3200.cpp"
#include "tcs3200_switch.hpp"

int main( void ){
    //aanmaken van pinnen voor de tcs3200
    auto s0 = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto s1 = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto s2 = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto s3 = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto sensor_out = hwlib::target::pin_in(hwlib::target::pins::d8);

    //aanmaken van de tcs3200 class
    auto chip = tcs3200(s0,s1,s2,s3,sensor_out);
    
    //aanmaken van pinnen voor de rail_switch
    auto pin0 = hwlib::target::pin_out(hwlib::target::pins::d22);
    auto pin1 = hwlib::target::pin_out(hwlib::target::pins::d23);

    auto pin2 = hwlib::target::pin_out(hwlib::target::pins::d24);
    auto pin3 = hwlib::target::pin_out(hwlib::target::pins::d25);

    auto but0 = hwlib::target::pin_in(hwlib::target::pins::d26);
    auto but1 = hwlib::target::pin_in(hwlib::target::pins::d27);

    //aanmaken van de rail_switch class
    auto switch0 = rail_switch(pin0,pin1);

    auto switch1 = rail_switch(pin2,pin3);

    
    rgb wagon0 = {0,0,0};
    rgb wagon1 = {0,0,0};

    //aanmaken van de tcs3200_switch class
    auto color_switch0 = tcs3200_switch(chip,switch0,wagon0);

    auto color_switch1 = tcs3200_switch(chip,switch1,wagon1);

    //starten van de tcs3200_switch
    while(true){
        color_switch0.start_with_external_loop();
        color_switch1.start_with_external_loop();
        if(but0.read()){
            wagon0 = chip.read_rgb();
        }
        if(but1.read()){
            wagon1 = chip.read_rgb();
        }
    }
    
}


