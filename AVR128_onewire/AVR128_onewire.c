/*
 * AVR128_onewire.c
 *
 * Created: 22.12.2023 19:16:41
 *  Author: Komputer_3
 */ 

#include "AVR128_onewire.h"

#include <avr/io.h>
#include <util/delay.h>

void OneWire_ResetPulse(){
	PORTA.DIRSET = PIN6_bm;
	PORTA.OUTCLR = PIN6_bm;
	_delay_us(500);
	PORTA.DIRCLR = PIN6_bm;
}

bool OneWire_DetectPresence(){
	int8_t iter = 100; //Adjust if needed
	bool present = false;
	_delay_us(60);
	PORTA.DIRCLR = PIN6_bm;
	PORTA.OUTSET = PIN5_bm; //OSC debug
	while(!present && iter > 0){
		present = !(PORTA.IN & PIN6_bm);
		iter--;
		_delay_us(1);
	}
	_delay_us(100);
	PORTA.OUTCLR = PIN5_bm; //OSC debug
	return present;
}

void OneWire_WriteData(uint64_t data, uint8_t bytes){
	for (uint8_t i=0; i<bytes*8; i++){
		PORTA.DIRSET = PIN6_bm;
		PORTA.OUTCLR = PIN6_bm;
		PORTA.OUTSET = PIN5_bm; //OSC debug
		if(data & (1 << i)){
			_delay_us(2);
		}
		else{
			_delay_us(75);
		}
		PORTA.OUTCLR = PIN5_bm; //OSC debug
		//_delay_us(2 + (70 * !(data & (1 << i)))); delays only accept const args so this won't work
		PORTA.DIRCLR = PIN6_bm;
		_delay_us(100);
	}
}

void OneWire_ReadData(uint8_t bytes){
	for (uint8_t i=0; i<bytes*8; i++){
		OneWire_Data[i/8] &= ~(1 << (i % 8));
		PORTA.DIRSET = PIN6_bm;
		PORTA.OUTCLR = PIN6_bm;
		_delay_us(2);
		PORTA.DIRCLR = PIN6_bm;
		//PORTA.OUTSET = PIN5_bm; //OSC debug
		_delay_us(5);
		OneWire_Data[i/8] |= ((PORTA.IN >> PIN6_bp /*i%3*/) & 1) << (i % 8);
		//PORTA.OUTCLR = PIN5_bm; //OSC debug
		_delay_us(60);
	}
	OneWire_ResetPulse();
}