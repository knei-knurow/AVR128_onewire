/*
 * AVR128_onewire.c
 *
 * Created: 22.12.2023 19:16:41
 *  Author: Komputer_3
 */ 

#include "AVR128_onewire.h"

#include <avr/io.h>
#include <util/delay.h>

bool OneWire_ResetPulse(){
	uint8_t retval;
	PORTA.DIRSET = PIN6_bm;
	PORTA.OUTCLR = PIN6_bm;
	_delay_us(500);
	PORTA.DIRCLR = PIN6_bm;
	
	_delay_us(70);
	retval = !(PORTA.IN & PIN6_bm);
	_delay_us(460);
	return retval;
}

void OneWire_WriteBit(uint8_t bit){
	if(bit){
		PORTA.OUTCLR = PIN6_bm;
		_delay_us(8);
		PORTA.OUTSET = PIN6_bm;
		_delay_us(65);
	}
	else{
		PORTA.OUTCLR = PIN6_bm;
		_delay_us(65);
		PORTA.OUTSET = PIN6_bm;
		_delay_us(5);
	}
}

void OneWire_WriteByte(uint8_t byte){
	PORTA.OUTSET = PIN6_bm;
	PORTA.DIRSET = PIN6_bm;
	for (uint8_t i=0; i<8; i++){
		OneWire_WriteBit(byte & 1);
		byte >>= 1;
	}
}

uint8_t OneWire_ReadBit(){
	uint8_t retval;
	PORTA.OUTCLR = PIN6_bm;
	PORTA.DIRSET = PIN6_bm;
	_delay_us(3);
	PORTA.DIRCLR = PIN6_bm;
	_delay_us(10);
	retval = (PORTA.IN & PIN6_bm) != 0;
	_delay_us(50);
	return retval;
}

uint8_t OneWire_ReadByte(){
	uint8_t retval = 0;
	for(uint8_t i = 1; i; i <<= 1){
		if(OneWire_ReadBit()){
			retval |= i;
		}
	}
	return retval;
}