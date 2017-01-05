/* Sunrise Alarm Clock */

//Including required libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "pinDefines.h"

//Defining buzzer related ports
#define ABuzz      PB0
#define ABuzz_DDR  DDRB
#define ABuzz_PORT PORTB

//Defining bit changer for buzzer
#define setBit(sfr, bit)     (_SFR_BYTE(sfr) |= (1 << bit))
#define clearBit(sfr, bit)   (_SFR_BYTE(sfr) &= ~(1 << bit))
#define toggleBit(sfr, bit)  (_SFR_BYTE(sfr) ^= (1 << bit))

//Declaring and initializing global variables
volatile int enabled = 1;
int printed = 0;
uint8_t sensitivity;
int delay;

void setSensitivity();
void setDelay();

//Button interrupt
ISR(PCINT2_vect)
{
  //Check if it the alarm is on
  if (bit_is_set(ABuzz_PORT, ABuzz))
  {
    //Turn the buzzer off
    clearBit(ABuzz_PORT, ABuzz);
    //Stop the loop
    enabled = 0;
  }
  else
  {
    /* I found this to be too annoying personally so I decided to comment it out

    //Ask user if to reset sensitivity
    printString("Would you like to reset the sensor's sensitivity? (Yes = 1)\n");
    uint8_t toReset = getNumber();
    receiveByte();
    if (toReset == 1) { setSensitivity(); }

    //Ask user if to reset delay
    printString("Would you like to reset the interrupt's delay? (Yes = 1)\n");
    toReset = getNumber();
    receiveByte();
    if (toReset == 1) { setDelay(); }
    */

    //Set and print success message
    enabled = 1;
    printString("You're all set! Off to sleep!\n");
  }

  /* Attempted to use delay to skip the second interrupt input but it didn't
     work as I hoped. So I decided to embrace it as a feature instead.
   */

  //Delay between interrupts to turn off alarm
  for(int i = 0; i < delay; i++)
  {
    _delay_ms(10);
  }

  //Reset the sensor to run again
  printed = 0;

  PCIFR |= (1 << PCIF2);
}

int main(void)
{
  //Setting up for light sensor
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS2);
  ADCSRA |= (1 << ADEN);

  //Setting up the button interrupt
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PD2);
  MCUCR |= (1 << PUD);
  sei();

  //Initializing USART
  initUSART();

  //Print title to string
  printString("---- Sunrise Alarm Clock ------\r\n");

  //Declaring variables
  uint16_t adcValue;
  uint8_t brightness;

  //Initialize buzzer
  setBit(ABuzz_DDR, ABuzz);
  setSensitivity();
  setDelay();

  //Main Loop
  while (1)
  {
    if (enabled > 0)
    {
      //Start ADC conversion
      ADCSRA |= (1 << ADSC);
      //Wait for the conversion to complete
      loop_until_bit_is_clear(ADCSRA, ADSC);
      //Get the ADC value
      adcValue = ADC;
      //Map it into a scale of 7
      brightness = (adcValue >> 7);

      //Check if the light is brighter than the selected sensitivity
      if (brightness > sensitivity)
      {
        if (printed == 0)
        {
          setBit(ABuzz_PORT, ABuzz);
          printString("WAKEUP!!!!\n");
          printed = 1;
        }
      }
    }
  }
  return 0;
}

void setSensitivity()
{
  do
  {
    //Get sensitivity input from user
    printString("What sensitivity do you want it to be? (Scale of 1 - 6)\n");
    sensitivity = getNumber();
    receiveByte();
  } while (sensitivity > 6 || sensitivity < 1);
}

void setDelay()
{
  do
  {
    //Get delay input from user
    printString("How long do you want the delay to be? (1 = 10ms, Scale of 0 - 200)\n");
    delay = getNumber();
    receiveByte();
  } while (delay > 200 || delay < 0);
}
