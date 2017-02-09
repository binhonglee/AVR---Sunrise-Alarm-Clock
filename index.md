# AVR - Sunrise Alarm Clock

This documentation is written around an ATMEGA168 programmed through an AVR. It might (should) be compatible with other microcontrollers but you will need to tweak the program and the set up a little bit here and there.

**For software side installation instruction, please go to [https://github.com/binhonglee/SunriseAlarmClock](https://github.com/binhonglee/SunriseAlarmClock)**

### Requirements

The parts that is used in building the project includes:
- [ATMEGA168](http://www.atmel.com/devices/ATMEGA168.aspx)
- Long breadboard
- Active Buzzer
- Photoresistor
- Button Interrupt
- 100uF 50V capacitor
- Resistor
- [USBtinyISP](https://learn.adafruit.com/usbtinyisp) - AVR programmer & SPI interface
- UART serial port
- Bunch of wires

Optional:
- LED
- Additional Resistor

### Putting it together

1. Solder your USBtinyISP according to the tutorial.

2. Put all the parts onto the breadboard according to this diagram. (If you do not have any LEDs or Resistors, ignore them)
![image](./diagram.png)

3. Connect everything together onto your computer.

4. (Optional) If you have the LEDs and Resistors connected, make sure the LEDs is lightened up.

5. Proceed to flash the microcontroller with the program following the instructions [here](https://github.com/binhonglee/AVR---Sunrise-Alarm-Clock).

6. Congratulations, you have it all put together!
