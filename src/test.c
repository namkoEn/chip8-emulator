#include <stdio.h>
#include "minunit.h"
#include "chip8.h"
#include "display.h"

CHIP8 chip8;

// Initialisation Test (All Properties are set to 0)
MU_TEST(test_chip8_initialise) {
    chip8_initialise(&chip8);
    mu_assert_int_eq(chip8.PC, 0x200);
    for (int i = 0; i < NUM_OF_REGISTERS; i++) {
        mu_assert_int_eq(chip8.V[i], 0);
    }
    mu_assert_int_eq(chip8.delay_timer, 0);
    mu_assert_int_eq(chip8.sound_timer, 0);
}

// Test Loading a ROM
MU_TEST(test_chip8_loadrom) {
    chip8_initialise(&chip8);
    chip8_loadrom(&chip8, "roms/test.rom");
    mu_assert_int_eq(chip8.memory[0x200], 0x60);
}

// Test Emulate Cycle
MU_TEST(test_chip8_emulatecycle) {
    chip8_initialise(&chip8);
    chip8.memory[0x200] = 0x60; // LD V0
    chip8.memory[0x201] = 0x12; // 0x12
    chip8_emulatecycle(&chip8);
    mu_assert_int_eq(chip8.V[0], 0x12);
    mu_assert_int_eq(chip8.PC, 0x202);
}

// Test Update Timers
MU_TEST(test_chip8_updatetimers) {
    CHIP8 chip8;
    chip8.delay_timer = 5;
    chip8.sound_timer = 4;

    chip8_updatetimers(&chip8);

    mu_assert_int_eq(chip8.delay_timer, 4);
    mu_assert_int_eq(chip8.sound_timer, 3);
}

// Test Display
MU_TEST(test_clearscreen) {
    CHIP8 chip8;
    chip8_initialise(&chip8);

    chip8.screen[5 * SCREEN_WIDTH + 10] = 1; // Manually set pixel (10, 5) to 1

    chip8.memory[0x200] = 0x00;  
    chip8.memory[0x201] = 0xE0; // CLS

    chip8_emulatecycle(&chip8);

    for (int i = 0; i < (SCREEN_HEIGHT * SCREEN_WIDTH); i++) { // Check all display bits are 0
        mu_assert_int_eq(chip8.screen[i], 0);
    }
}

// Test Draw Sprite
MU_TEST(test_drawsprite) {
    CHIP8 chip8;
    chip8_initialise(&chip8);

    chip8.memory[0x300] = 0b10101010; // Sprite data at memory location 300

    // Set necessary arguments
    chip8.I = 0x300;
    uint8_t x = 2;   
    uint8_t y = 3;
    uint8_t height = 1; 

    // First draw - No Collisions
    chip8.V[0xF] = 0;
    chip8_drawsprite(&chip8, x, y, height);

    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 2], 1);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 3], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 4], 1);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 5], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 6], 1);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 7], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 8], 1);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 9], 0);

    // Second draw - Collisions
    chip8.V[0xF] = 0;
    chip8_drawsprite(&chip8, x, y, height);

    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 2], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 3], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 4], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 5], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 6], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 7], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 8], 0);
    mu_assert_int_eq(chip8.screen[(3 * SCREEN_WIDTH) + 9], 0);

    // Check VF for Collision
    mu_assert_int_eq(chip8.V[0xF], 1);
}

// Run Tests
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_chip8_initialise);
    MU_RUN_TEST(test_chip8_loadrom);
    MU_RUN_TEST(test_chip8_emulatecycle);
    MU_RUN_TEST(test_chip8_updatetimers);
    MU_RUN_TEST(test_clearscreen);
    MU_RUN_TEST(test_drawsprite);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}