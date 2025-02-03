# so_long

## Overview
**so_long** is a 2D game project developed as part of the Hive/42 curriculum. The player navigates through a map, collecting all collectibles before reaching the exit while avoiding obstacles. The game is built using **MiniLibX**, a lightweight graphics library.

## Features
- **Pathfinding Algorithm**: Ensures that all collectibles and the exit are reachable before starting the game.
- **MLX42 Graphics**: Renders the game environment with sprites and handles player movement.
- **User Input Handling**: Uses keyboard controls to move the player.
- **Dynamic Map Parsing**: Reads `.ber` map files and validates their structure.
- **Memory Management**: Proper allocation and deallocation of resources to prevent memory leaks.

## Installation
### Prerequisites
- **Make** and **GCC** (installed by default on most Linux/macOS systems)
- **MLX42** (Ensure it is installed or use the provided version in the project)

### Clone the Repository
```
git clone https://github.com/Mark-Byrne-Codes/Hive-42-Studies.git
cd Hive-42-Studies/so_long
```
### Build The Program
```
make
```
This compiles the game and generates the so_long executable.

### Running the Game
