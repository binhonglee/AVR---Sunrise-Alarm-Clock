# Sunrise Alarm Clock

The program is written for an ATMEGA168 programmed through an AVR.

**For a comprehensive guide (or hardware side tutorial), please go to [https://binhonglee.github.io/SunriseAlarmClock](https://binhonglee.github.io/SunriseAlarmClock)**

### Requirements

This program requires the following stuffs to work on your computer:
- avrdude
- make
- cmake
- UART terminal

### Installation

1. Clone this repository
```sh
$ git clone https://github.com/binhonglee/SunriseAlarmClock/
```

2. (Optional) Check the Makefile to see if it fits your microcontroller and controller.

3. Open your UART terminal.

4. Make sure your UART terminal is connected to your USART component.

5. Flash the microcontroller
```sh
$ make flash
```

### Removal

To remove this program from your computer, do the following:

1. Uninstall every other thing you installed from the requirements that you no longer need.

2. Delete this folder
```sh
$ cd ../
$ rm -rf SunriseAlarmClock
```

###### Author's note :
Most of the program has line by line comments written so it shouldn't be too hard to understand and to tweak it for your use.
