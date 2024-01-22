/*
 * AVR128_onewire.h
 *
 * Created: 22.12.2023 19:16:16
 *  Author: Komputer_3
 */ 


#ifndef AVR128_ONEWIRE_H_
#define AVR128_ONEWIRE_H_

#include <stdbool.h>
#include <stdint.h>

#define ONEWIRE_SEARCH_ROM 0xF0			//ROM commands
#define ONEWIRE_READ_ROM 0x33
#define ONEWIRE_MATCH_ROM 0x55
#define ONEWIRE_SKIP_ROM 0xCC
#define ONEWIRE_ALARM_SEARCH 0xEC

#define ONEWIRE_CONVERT_T 0x44			//Temperature command

#define ONEWIRE_SCRATCHPAD_WRITE 0xBE	//Memory commands
#define ONEWIRE_SCRATCHPAD_READ 0x4E
#define ONEWIRE_SCRATCHPAD_COPY 0x48
#define ONEWIRE_RECALL_E2 0xB8
#define ONEWIRE_READ_POWER_SUPPLY 0xB4

void OneWire_ResetPulse();
bool OneWire_DetectPresence();
void OneWire_WriteData(uint64_t data, uint8_t bytes);
void OneWire_ReadData(uint8_t bytes);

volatile uint8_t OneWire_Data[9];

#endif /* AVR128_ONEWIRE_H_ */