/*
 * AVR128_test.c
 *
 * Created: 22.12.2023 18:44:02
 * Author : Komputer_3
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "AVR128_onewire.h"

int main(void)
{
	_PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc); // Set clock to 24 MHz
	
    PORTD.DIRSET = 0b11111110; // Every PDx except PD0 to output
	PORTA.DIRSET = PIN5_bm;
	
	uint8_t dataHolder;
	
    while (1) 
    {
		//PORTD.OUTTGL = 0b11111110;
		//_delay_ms(1000);
		//PORTD.OUTTGL = PIN7_bm;
		
		OneWire_ResetPulse();
		if (OneWire_DetectPresence()) //this whole schmuck needs to repeat in read
		{
			OneWire_WriteData(ONEWIRE_SKIP_ROM, 1);
			OneWire_WriteData(ONEWIRE_SCRATCHPAD_READ, 1);
			OneWire_ReadData(9);
			/*OneWire_WriteData(ONEWIRE_CONVERT_T, 1);
			_delay_ms(1000);
			OneWire_ResetPulse();
			(void)OneWire_DetectPresence();
			OneWire_WriteData(ONEWIRE_SKIP_ROM, 1);
			OneWire_WriteData(ONEWIRE_SCRATCHPAD_READ, 1);
			OneWire_ReadData(2);
			_delay_ms(2000);
			dataHolder = 0;
			//dataHolder = (OneWire_Data[0] >> 3) | (OneWire_Data[1] << 5);
			dataHolder = OneWire_Data[0];
			PORTD.OUTSET = dataHolder;
			PORTD.OUTCLR = ~dataHolder;*/
		}
		_delay_ms(1000);
    }
}

