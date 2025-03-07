#include "chip8.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialise the Struct with Registers Containing 0
void chip8_initialise(CHIP8 *chip8) {
    memset(chip8, 0, sizeof(CHIP8)); 
    chip8->PC = 0x200; // Programs Start at 0x200
}

// Load ROM into Main Memory
void chip8_loadrom(CHIP8 *chip8, const char *filename) {
    FILE *rom = fopen(filename, "rb"); // Read ROM in Binary Mode
    if (rom == NULL) {
        printf("ROM failed to load. Name: %s\n", filename);
        exit(1);
    }

    // Get Size of ROM
    fseek(rom, 0, SEEK_END);
    long size = ftell(rom);
    fseek(rom, 0, SEEK_SET);  
    
    // Move ROM into Main Memory
    fread(&chip8->memory[0x200], size, 1, rom);
    fclose(rom);
}

void chip8_emulatecycle(CHIP8 *chip8) {
    // Fetches 2 Bytes from Memory, Manipulates them into Single 16 Bit opcode.
    uint16_t opcode = (chip8->memory[chip8->PC] << 8) | chip8->memory[chip8->PC + 1];
    
    // Switch Cases for opcodes
    switch (opcode & 0xF000) {
        case 0x0000: // CLS
            // Differentiate between 0x00E0 and 0x00EE
            switch(opcode) {
                case 0x00E0:
                    chip8_clearscreen(chip8);
                    break;

                default:
                    printf("Not a valid opcode: %X\n", opcode);
                    break;
            }
        
        case 0x1000: // JP addr
            chip8->PC = opcode & 0x0FFF;
            break;
        
        case 0x6000: // LD Vx, byte
            chip8->V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            break;

        case 0x7000: // ADD Vx, byte
            chip8->V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            break;

        case 0xD000: { // DRW Vx, Vy, nibble
            uint8_t x = chip8->V[(opcode & 0x0F00) >> 8];
            uint8_t y = chip8->V[(opcode & 0x00F0) >> 4];
            uint8_t height = opcode & 0x000F;
            chip8_drawsprite(chip8, x, y, height);
            break;
        }
        
        default:
            printf("Not a Valid Opcode: %X\n", opcode);
            break;
    }
    chip8->PC += 2; // Increments Twice - Opcode is two bites
}

void chip8_updatetimers(CHIP8 *chip8) {
    if (chip8->delay_timer > 0) chip8->delay_timer--;
    if (chip8->sound_timer > 0) chip8->sound_timer--;
}