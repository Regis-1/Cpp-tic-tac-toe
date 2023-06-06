# Cpp-tic-tac-toe
C++ tic tac toe game made with raylib library.

## Installation
Repository uses the CMake as a primary building tool. Procedure to install the game with this tool below.
### Linux
1. ```mkdir build && cd build```
2. ```cmake -S .. -B .```
3. ```make```
4. ```./Cpp-ttt```

### Windows
1. Due to the raylib's naming conflicts with some of the Windows functions there is the need to change names of the following function in the raylib's header file:
  1. Open ```raylib.h``` in ```extlibs/raylib/raylib/include```
  2. Change the name of the ```DrawTextEx```, ```...``` in the header file and then adjust the names in ```src``` directory to be the same
3. Use CMake cli similar to Linux procedure or use CMake GUI application
4. Build the game with selected tool e.g. ```ninja``` or ```mingw32-make```
5. Run ```Cpp-ttt.exe```

## Features
### Current version: v0.1

- Play game with other person with the hotseat mode
- Play game with the opponent via LAN connection

### To be added
- Play game with AI opponent based on the minmax algorithm

## Presentation:
![image](https://github.com/Regis-1/Cpp-tic-tac-toe/assets/59539717/051d4846-250a-4788-8d17-00ad1035fbb1)
![image](https://github.com/Regis-1/Cpp-tic-tac-toe/assets/59539717/db9fb6b5-aad1-441e-8e6d-993b2e1c25c1)
![image](https://github.com/Regis-1/Cpp-tic-tac-toe/assets/59539717/9c434bc6-1346-4bc4-bc70-d3bf4f4ff644)
