#include "hwlib.hpp"
#include "rail_switch.hpp" //for rail_switch
#include "tcs3200.hpp" //for tcs3200 and rgb

/// @brief Layer between the tcs3200 class and the rail_switch class.
/// @details This class is the funtioning layer between the tcs3200 and the rail_switch. \n \n The tcs3200 reads the color. The code compairs this with the given rgb stuct. \n If the color is close enough the switch wil change from going straight to going to the other direction. \n If the time has passed and the color is no longer the samen then the switch wil return to going straight.
/// @see tcs3200, rail_switch
class tcs3200_switch{
private:
    /// @brief chip variable using tcs3200 class
    tcs3200& chip;
    /// @brief s variable using rail_switch class
    rail_switch& s;
    /// @brief color variable using rgb struct
    rgb color;
    /// @brief switch_check variable
    bool switch_check = false;
public:
    /// @brief wait_time variable for start().
    int wait_time = 4000;

    /// @brief Constructor of the tcs3200_switch class.
    /// @details This constructor puts the chip, switch and color into the members.
    /// @param chip_ This is a tcs3200 class.
    /// @param s_ This is the switch that wil be used.
    /// @param color_ This is the color for the switching.
    tcs3200_switch(tcs3200& chip_, rail_switch& s_, const rgb& color_):
        chip(chip_),
        s(s_),
        color(color_)
    {}

    /// @brief Start funtion.
    /// @details This funtion starts the comparting of the color to the sensor and switch accordingly.
    /// @note This uses a internal while loop, which makes it so you cant do anything else. For using more than 1 switch or ding other things i recomend using start_with_external_loop().
    /// @see start_with_external_loop()
    void start(){
        while(true){
            start_with_external_loop();
        }
    }

    /// @brief 2nd Start funtion.
    /// @details This funtion starts the comparting of the color to the sensor and switch accordingly without an internal loop.
    /// ### Example with more than 1 switch:
    /// ~~~.cpp
    /// while(true){
    ///     tcs3200_switch1.ststart_with_external_loop();
    ///     tcs3200_switch2.ststart_with_external_loop();
    ///     tcs3200_switch3.ststart_with_external_loop();
    /// }
    /// ~~~
    /// @note This class has a variable called wait_time, The default = 4000 (in mili seconds), this can be changed by changing the wait_time variable.
    void start_with_external_loop(){
        if(chip.check(color) && not switch_check){
            s.other_direction();
            switch_check = true;
            hwlib::wait_ms(wait_time);
        }else if(not chip.check(color) && switch_check){
            s.straight();
            switch_check = false;
        }
    }
};