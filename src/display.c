#include "display.h"
#include "chip8.h"
#include <string.h>
#include <stdio.h>

void chip8_clearscreen(CHIP8 *chip8) {
    memset(chip8->screen, 0, sizeof(chip8->screen));
}

void chip8_drawsprite(CHIP8 *chip8, uint8_t x, uint8_t y, uint8_t height) {
    chip8->V[0xF] = 0; // Reset collision

    for (int row = 0; row < height; row++) {
        uint8_t sprite_byte = chip8->memory[chip8->I + row];

        for (int col = 0; col < 8; col++) {
            uint8_t pixel = (sprite_byte >> (7 - col)) & 1;
            uint16_t index = ((y + row) % SCREEN_HEIGHT) * SCREEN_WIDTH + ((x + col) % SCREEN_WIDTH);

            if (chip8->screen[index] == 1 && pixel == 1) {
                chip8->V[0xF] = 1; // Set collision if pixel is erased
            }

            chip8->screen[index] ^= pixel; // XOR the pixel
        }
    }
}

void chip8_printscreen(CHIP8 *chip8) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            printf(chip8->screen[y * SCREEN_WIDTH + x] ? "█" : " ");
        }
        printf("\n");
    }
    printf("\n");
}