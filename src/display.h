#ifndef DISPLAY_H
#define DISPLAY_H

#include "chip8.h"

// Prototypes to Stop Errors
uint8_t x;
uint8_t y;
uint8_t height;
void chip8_clearscreen(CHIP8 *chip8);
void chip8_drawsprite(CHIP8 *chip8, uint8_t x, uint8_t y, uint8_t height);
void chip8_printscreen(CHIP8 *chip8);

#endif