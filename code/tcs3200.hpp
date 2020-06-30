#pragma once //only include once
#include "hwlib.hpp"

/// @brief This stuct contains the ints of the color.
/// @details This struct contains the int of the color. It is used with the tcs3200 class to check if the input from the sensos is roughly the same as the rgb input.
struct rgb{
    /// @brief red variable
    int red;
    /// @brief green variable
    int green;
    /// @brief blue variable
    int blue;
};

/// @brief TCS3200 sensor.
/// @details This class is made for the TCS3200 color sensor. The TCS3200 outputs a square wave with differing frequency. \n ![ ](tcs3200_1.png) \n ![Working of the TCS3200](tcs3200_2.png) \n The TCS3200 has a current to frequency converter build in. \n This class uses that frequency to convert it back to the color value. \n \n Link to the <a href="https://www.mouser.com/catalog/specsheets/tcs3200-e11.pdf">TCS3200 Datasheet</a>
/// @see rgb
class tcs3200{
private:
    /// @brief s0 variable using pin_out from hwlib PRIVATE
    hwlib::pin_direct_from_out_t s0;
    /// @brief s1 variable using pin_out from hwlib PRIVATE
    hwlib::pin_direct_from_out_t s1;
    /// @brief s2 variable using pin_out from hwlib PRIVATE
    hwlib::pin_direct_from_out_t s2;
    /// @brief s3 variable using pin_out from hwlib PRIVATE
    hwlib::pin_direct_from_out_t s3;
    /// @brief sensor_out variable using pin_in from hwlib PRIVATE
    hwlib::pin_direct_from_in_t sensor_out;

    /// @brief Read funtion
    /// @details Reads the output of the sensor. This funtion does nothing if the sensor is in sleep mode.
    /// @returns Frequency (in ns) as an int.
    /// @attention This funtion is private and can only be used by the read funtions of the individual colors.
    int read(){
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
            if(i > 10000){ //fail safe
                x = false;
            }
            i++;
            hwlib::wait_us(1);
        }
        return i;
    }

public:
    /// @brief accuracy variable for check().
    int accuracy = 10; //accuracy for check()

    /// @brief Constructor of the tcs3200 class.
    /// @details This constructor sets the pins as members and sets the chip's frequency scaler to 20%.
    /// @param s0_ This is a hwlib::target::pin_out for the s0 pin on the sensor.
    /// @param s1_ This is a hwlib::target::pin_out for the s1 pin on the sensor.
    /// @param s2_ This is a hwlib::target::pin_out for the s2 pin on the sensor.
    /// @param s3_ This is a hwlib::target::pin_out for the s3 pin on the sensor.
    /// @param sensor_out_ This is a hwlib::target::pin_in for the sensor_out pin on the sensor.
    tcs3200(hwlib::target::pin_out & s0_,
            hwlib::target::pin_out & s1_,
            hwlib::target::pin_out & s2_,
            hwlib::target::pin_out & s3_,
            hwlib::target::pin_in & sensor_out_):
            s0(s0_),
            s1(s1_),
            s2(s2_),
            s3(s3_),
            sensor_out(sensor_out_)
    {
        //sets the frequency scaler to 20%
        s0.write(true);
        s1.write(false);
    }

    /// @brief Reads the red color as an int
    /// @details Reads the sensor for the red color. The return is an average of 5 runs.
    /// @return Frequency (in ns) as an int.
    /// @see read()
    int read_red(){
        //set chip to read red
        s2.write(false);
        s3.write(false);
        int totaal = 0;
        for(int i = 0; i < 5; i++){
            totaal += read();
        }
        return totaal / 5.0;
    }

    /// @brief Reads the green color as an int
    /// @details Reads the sensor for the green color. The return is an average of 5 runs.
    /// @return Frequency (in ns) as an int.
    /// @see read()
    int read_green(){
        //set chip to read green
        s2.write(true);
        s3.write(true);
        int totaal = 0;
        for(int i = 0; i < 5; i++){
            totaal += read();
        }
        return totaal / 5.0;
    }

    /// @brief Reads the blue color as an int
    /// @details Reads the sensor for the blue color. The return is an average of 5 runs.
    /// @return Frequency (in ns) as an int.
    /// @see read()
    int read_blue(){
        //set chip to read blue
        s2.write(false);
        s3.write(true);
        int totaal = 0;
        for(int i = 0; i < 5; i++){
            totaal += read();
        }
        return totaal / 5.0;
    }

    /// @brief Turns off the sensor.
    /// @details This funtion sets s0 and s1 to false. This means that the sensor goes into sleep mode.
    void off(){
        s0.write(false);
        s1.write(false);
    }

    /// @brief Checks the color to a rgb variable.
    /// @details This funtion checks the sensor data to the given rgb variable.
    /// @param color This is a rgb variable used for the check.
    /// @returns A rgb variable
    /// @note This class has a variable called accuracy, The default = 10, this can be changed by changing the accuracy variable.
    /// @see read_red(), read_green(), read_blue()
    bool check(const rgb& color){
        int x1 = read_red() - color.red, x2 = read_green() - color.green, x3 = read_blue() - color.blue;
        if(x1 < 0){x1*=-1;}
        if(x2 < 0){x2*=-1;}
        if(x3 < 0){x3*=-1;}
        if(x1 <= accuracy && x2 <= accuracy && x3 <= accuracy){
            return true;
        }return false;
    }

    /// @brief Reads the color as a rgb variable.
    /// @details This funtion reads the color of the sensor and returns the colors as a rgb variable.
    /// @see rgb
    rgb read_rgb(){
        rgb tmp = {read_red(),read_green(),read_blue()};
        return tmp;
    }
};