@mainpage Introduction

*This is my libary for using the tcs3200 color sensing chip cin c++.*\n
\n
It includes a class for interacting with the tcs3200 if this is all that your after only include "tcs3200.hpp"\n
If you want to use the rail_switch class use "rail_switch.hpp". And use "tcs3200_switch.hpp" for using the switch and the tcs3200.
\n
**This libary has 3 main classes: tcs3200, rail_switch and tcs3200_switch:** \n
\n
*tcs3200:* \n
This class is used for reading the colors of the tcs3200 chip. \n
\n
*rail_switch:* \n
This class is used for controlling the direction of the mode train switch. \n
\n
*tcs3200_switch:* \n
This class is the funtioning layer between the tcs3200 and the rail_switch. \n
\n
*HWLIB:* \n
This libary uses the libary  <a href="https://github.com/wovo/hwlib">HWLIB</a> to comunicate with the arduino. Check the @ref HWLIB page for more information.
\n
\n
*Made by: Daan Kerbusch*\n
