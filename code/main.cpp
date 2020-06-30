#include "hwlib.hpp"
#include "rail_switch.hpp"
#include "tcs3200.hpp"
#include "tcs3200_switch.hpp"

int main( void ){
    //configuring the pins of the tcs3200
    auto s0 = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto s1 = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto s2 = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto s3 = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto sensor_out = hwlib::target::pin_in(hwlib::target::pins::d8);

    //make the tcs3200 class
    auto chip = tcs3200(s0,s1,s2,s3,sensor_out);
    
    //making the pins for switches and the buttons
    auto pin0 = hwlib::target::pin_out(hwlib::target::pins::d22);
    auto pin1 = hwlib::target::pin_out(hwlib::target::pins::d23);

    auto pin2 = hwlib::target::pin_out(hwlib::target::pins::d24);
    auto pin3 = hwlib::target::pin_out(hwlib::target::pins::d25);

    auto but0 = hwlib::target::pin_in(hwlib::target::pins::d26);
    auto but1 = hwlib::target::pin_in(hwlib::target::pins::d27);

    //making the switch classes
    auto switch0 = rail_switch(pin0,pin1);

    auto switch1 = rail_switch(pin2,pin3);

    //giving the wagon variables the value of 0,0,0
    rgb wagon0 = {0,0,0};
    rgb wagon1 = {0,0,0};

    //making the tcs3200_switch classes
    auto color_switch0 = tcs3200_switch(chip,switch0,wagon0);

    auto color_switch1 = tcs3200_switch(chip,switch1,wagon1);

    //starting of the main code
    chip.accuracy = 5; //set the accuracy to 5
    while(true){
        color_switch0.start_with_external_loop();
        color_switch1.start_with_external_loop();
        if(but0.read()){ //change color if the button is pressed
            wagon0 = chip.read_rgb();
            color_switch0.update_color(wagon0);
        }
        if(but1.read()){
            wagon1 = chip.read_rgb();
            color_switch1.update_color(wagon1);
        }
        //uncomment the next line if you want to show the output of the chip
        //hwlib::cout << chip.read_red() << " " << chip.read_green() << " " << chip.read_blue() << "\n";
    }
    
}