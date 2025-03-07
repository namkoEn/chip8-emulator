#include <stdio.h>
#include "chip8.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No ROM Given\n");
        return 1;
    }

    CHIP8 chip8;
    chip8_initialise(&chip8);
    chip8_loadrom(&chip8, argv[1]);

    while (1) {
        chip8_emulatecycle(&chip8);
    }
    return 0;
}