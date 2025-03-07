# CHIP-8 Emulator

A CHIP-8 emulator written in C using SDL2 for display and input handling.

## Features
- Loads and executes CHIP-8 ROMs
- Implements key CHIP-8 opcodes
- Supports display rendering and keyboard input
- Unit tests using MinUnit

## Installation & Compilation

### Prerequisites
Ensure you have the following installed:
- clang or gcc (C compiler)
- make (for building the project)
- SDL2 (for graphics and input)

### Building the Emulator
Run the following command to compile the project:
```sh
make
```

### Running the Emulator
To run the emulator with a ROM file:
```sh
./chip8 roms/<your_rom_file.ch8>
```

### Running Unit Tests
To run the test suite:
```sh
make test
```

## Controls
| CHIP-8 Key | Keyboard Mapping |
|------------|-----------------|
| 1 2 3 C    | 1 2 3 4         |
| 4 5 6 D    | Q W E R         |
| 7 8 9 E    | A S D F         |
| A 0 B F    | Z X C V         |

## Project Structure
```
chip8-emulator/
│── src/               # Source code
│   ├── chip8.c        # CHIP-8 core implementation
│   ├── display.c      # Display handling (SDL2)
│   ├── input.c        # Keyboard input handling
│   ├── main.c         # Entry point of the emulator
│── include/           # Header files
│── roms/              # Folder for test ROMs
│── test/              # Unit tests
│── Makefile           # Build script
│── README.md          # Project documentation
```

## How It Works
The emulator follows the CHIP-8 execution cycle:
1. **Fetch**: Read the next opcode from memory
2. **Decode**: Determine which instruction to execute
3. **Execute**: Perform the operation (e.g., update registers, draw to screen)

## Resources
- [CHIP-8 Instruction Set Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Cowgod’s CHIP-8 Technical Reference](http://mattmik.com/files/chip8/mastering/chip8.html)

## License
This project is open-source under the MIT License.
