#ifndef CHIP8_H
#define CHIP8_H

// Header File for Fixed-Size Integers
#include <stdint.h>

// CHIP-8 System Specs
#define KEYPAD_KEYS 16
#define NUM_OF_REGISTERS 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

// CHIP-8 Struct, Represents the State of the Machine.
typedef struct
{
    uint8_t memory[MEMORY_SIZE]; // 4KB Main Memory
    uint8_t V[NUM_OF_REGISTERS]; // 16 General-Purpose Registers, V0 to VF
    uint16_t PC; // Program Counter
    uint16_t I; // Index Register
    uint8_t SP; // Stack Pointer
    uint16_t stack[STACK_SIZE]; // Call Stack for Subroutines
    uint8_t delay_timer; // When Active, Decrements at 60Hz
    uint8_t sound_timer; // When Active, Decrements at 60Hz
    uint8_t screen[SCREEN_HEIGHT * SCREEN_WIDTH]; // 64x32 Monochrome Display
    uint8_t keypad[KEYPAD_KEYS]; // Stores Pressed Key States
} CHIP8;

// Prototypes to Stop Errors
void chip8_initialise(CHIP8 *chip8);
void chip8_loadrom(CHIP8 *chip8, const char *filename);
void chip8_emulatecycle(CHIP8 *chip8);
void chip8_updatetimers(CHIP8 *chip8);

#endif