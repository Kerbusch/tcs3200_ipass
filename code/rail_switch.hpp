#pragma once //only include once
#include "hwlib.hpp"

/// @brief class for controlling a model train switch
/// @details This class is used for controlling the solenoid int the switch of a model train. \n The funtions have time limters so the solenoid wont burn out. \n \n The output of the arduino pins can be used with a transistor if you have a DC switch. otherwise it can be used with relays.
class rail_switch{
private:
    /// @brief Pin used for making the switch go straight. PRIVATE
    hwlib::pin_direct_from_out_t pin0; //pin for going straight
    /// @brief Pin used for making the switch go the other direction. PRIVATE
    hwlib::pin_direct_from_out_t pin1; //pin for going in the other direction
    /// @brief Boolian that makes sure that the swicht can't go in 2 directions PRIVATE
    bool heading = false; //true = straight
public:
    /// @brief Constructor of the rail_switch class.
    /// @details This constructor sets the pins as members and 'resets' the switch.
    /// @param pin0_ This is a hwlib::target::pin_out for going straight.
    /// @param pin1_ This is a hwlib::target::pin_out for going the other direction.
    rail_switch(hwlib::target::pin_out & pin0_,hwlib::target::pin_out & pin1_):
        pin0(hwlib::direct(pin0_)),
        pin1(hwlib::direct(pin1_))
    {
        straight();
    }

    /// @brief Makes the switch go straight.
    /// @details This funtion makes the switch go straight by activating the pin for 0.4 seconds. This is to make sure that the solenoid doesn't burn out.
    void straight(){
        if(not heading){
            pin0.write(true);
            //pin0.flush();
            hwlib::wait_ms(400);
            pin0.write(false);
            //pin0.flush();
            heading = true;
        }
    }

    /// @brief Makes the switch go the other direction.
    /// @details This funtion makes the switch go the other direction by activating the pin for 0.4 seconds. This is to make sure that the solenoid doesn't burn out.
    void other_direction(){
        if(heading){
            pin1.write(true);
            //pin1.flush();
            hwlib::wait_ms(400);
            pin1.write(false);
            //pin1.flush();
            heading = false;
        }
    }
};