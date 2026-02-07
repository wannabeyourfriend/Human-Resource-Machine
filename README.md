# Human Resource Machine

A Qt6-based implementation of the Human Resource Machine game, a puzzle game that teaches programming concepts through assembly-like instructions.

![Screenshot 1](https://github.com/user-attachments/assets/ccc05926-e640-4e90-b852-49c746f21fc3)
![Screenshot 2](https://github.com/user-attachments/assets/01077907-8a31-4791-b076-c454ba0d5ec0)
![Screenshot 3](https://github.com/user-attachments/assets/ecc8a4c3-9833-471a-9275-9552b03191cd)
![Screenshot 4](https://github.com/user-attachments/assets/3a9d4c60-4711-4364-83b8-36809a977973)
![Screenshot 5](https://github.com/user-attachments/assets/dca70c4d-cef0-44fd-b586-0b1ab856c7f4)

## Description

This project is a recreation of the Human Resource Machine game built using Qt6. The game challenges players to solve puzzles by programming a virtual worker using simple assembly-like instructions. Players must read data from an inbox, process it according to specific requirements, and deliver results to an outbox.

The implementation includes:
- A complete game engine supporting all standard Human Resource Machine commands
- Interactive UI built with Qt6 for visual programming
- Multiple levels with increasing difficulty
- Real-time execution visualization
- Support for custom level definitions

## Features

- **Qt6-Based Interface**: Modern cross-platform GUI using Qt6 framework
- **Visual Programming**: Drag-and-drop interface for assembling instructions
- **Multiple Game Levels**: Progressive difficulty from basic to advanced programming concepts
- **Real-Time Execution**: Watch your program execute step-by-step with visual feedback
- **Level Editor Support**: Custom level definitions and test cases
- **Comprehensive Testing**: Extensive test suite for validation and OJ support
- **Pause and Debug**: Pause execution and inspect program state

## Installation

### Prerequisites

- Qt6 (tested with Qt 6.x)
- C++17 compatible compiler
- CMake or qmake

### Build from Source

1. Clone the repository:
```bash
git clone https://github.com/wannabeyourfriend/Human-Resource-Machine.git
cd Human-Resource-Machine
```

2. Build the project:
```bash
# Using qmake
qmake human-resource-machine.pro
make

# Or using CMake (if CMakeLists.txt is available)
mkdir build && cd build
cmake ..
make
```

3. Run the executable:
```bash
./human-resource-machine
```

## Usage

### Playing the Game

1. Launch the application
2. Select a level from the level menu
3. Read the task description and requirements
4. Drag and drop instructions to program your worker
5. Click "Run" to execute your program
6. Debug and iterate until your solution passes all test cases

### Project Structure

- `human-resource-machine/` - Main game source code
  - `main.cpp` - Application entry point
  - `humanresourcemachine.cpp/h` - Core game logic
  - `ui_*_init.cpp` - UI initialization for different screens
  - `main_game_*.cpp` - Game execution logic
- `levels/` - Level definitions and test cases
- `test/` - Test cases for online judge validation
- `BasicFunctions/` - Basic function implementations
- `material/` - Game assets and resources
- `oj_main.cpp` - Online judge main entry point

## License

This project is provided for educational purposes. Please refer to the original Human Resource Machine game by Tomorrow Corporation for the official version.

## Acknowledgments

- Original game concept by [Tomorrow Corporation](https://tomorrowcorporation.com/)
- Built with [Qt6](https://www.qt.io/)
