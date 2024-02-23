/*
 * AVR128_onewire.h
 *
 * Created: 22.12.2023 19:16:16
 *  Author: Komputer_3
 */ 


#ifndef AVR128_ONEWIRE_H
#define AVR128_ONEWIRE_H 

#include <stdbool.h>
#include <stdint.h>

#define ONEWIRE_SEARCH_ROM 0xF0			//ROM commands
#define ONEWIRE_READ_ROM 0x33
#define ONEWIRE_MATCH_ROM 0x55
#define ONEWIRE_SKIP_ROM 0xCC
#define ONEWIRE_ALARM_SEARCH 0xEC

#define ONEWIRE_CONVERT_T 0x44			//Temperature command

#define ONEWIRE_SCRATCHPAD_WRITE 0x4E	//Memory commands
#define ONEWIRE_SCRATCHPAD_READ 0xBE
#define ONEWIRE_SCRATCHPAD_COPY 0x48
#define ONEWIRE_RECALL_E2 0xB8
#define ONEWIRE_READ_POWER_SUPPLY 0xB4

bool OneWire_ResetPulse();
void OneWire_WriteBit(uint8_t bit);
void OneWire_WriteByte(uint8_t byte);
uint8_t OneWire_ReadBit();
uint8_t OneWire_ReadByte();

#endif /* AVR128_ONEWIRE_H */