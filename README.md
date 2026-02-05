# Dhurandhar
Dhurandhar - Action Survival Game A top-down shooter game built with Qt 6 QML and C++ where you fight against relentless enemies in an intense survival challenge!
 About The Game
Dhurandhar is an action-packed survival shooter where you must eliminate all enemies while avoiding their deadly pursuit. Inspired by classic top-down shooters, the game features smooth movement, strategic shooting mechanics, and intense enemy AI that will chase you relentlessly!
🌟 Key Features

Smooth Player Movement: Navigate using WASD keys with responsive controls
4-Directional Shooting: Fire bullets in up, down, left, and right directions
Intelligent Enemy AI: Enemies chase the player and adapt their direction dynamically
Collision Detection: Advanced physics-based collision system for bullets and enemies
Score Tracking: Earn 100 points for each enemy eliminated
Game Over System: Die when enemies catch you
Level Completion: Win by defeating all enemies
Beautiful UI: Custom screens for game over and victory with restart functionality
Optimized Performance: Runs at smooth 30 FPS with efficient game loop

🎮 How to Play
Controls

W - Move Up
A - Move Left
S - Move Down
D - Move Right
SPACE - Shoot bullet in facing direction
R - Restart game (when game over or level complete)

Objective

Eliminate all 6 enemies by shooting them
Avoid getting caught by enemies
Maximize your score!

Game Mechanics

Player starts at the center of the screen
6 enemies spawn at different positions
Enemies continuously chase the player
Each bullet kill earns 100 points
Game ends if enemy touches player
Victory when all enemies are defeated

🛠️ Technical Details
Technologies Used

Qt 6 - Cross-platform application framework
QML - Declarative UI language
C++17 - Core game logic
CMake - Build system

Architecture
dhurandhar/
├── GameController.h/cpp   # Core game logic and state management
├── Player.h              # Player entity structure
├── Enemy.h               # Enemy entity structure
├── Bullet.h              # Bullet entity structure
├── Main.qml              # Application entry point
├── GameView.qml          # Main game view and UI
├── PlayerItem.qml        # Player visual component
├── EnemyItem.qml         # Enemy visual component
├── BulletItem.qml        # Bullet visual component
└── CMakeLists.txt        # Build configuration
Game Loop

Runs at 33ms intervals (~30 FPS)
Updates player position based on keyboard input
Moves all bullets and handles boundary detection
Updates enemy AI to chase player
Checks for collisions (bullet-enemy, player-enemy)
Emits signals to update QML UI

Collision System

Bullet vs Enemy: Distance-based detection with 40-pixel threshold
Player vs Enemy: Distance-based detection with 50-pixel threshold
Uses Euclidean distance calculation for accurate hit detection

📋 Prerequisites

Qt 6.0 or higher
CMake 3.16 or higher
C++17 compatible compiler
Qt Quick and Qt Multimedia modules

🚀 Installation & Build
Clone the Repository
bashgit clone https://github.com/yourusername/dhurandhar.git
cd dhurandhar
Build with CMake
bashmkdir build
cd build
cmake ..
cmake --build .
Run the Game
bash./appdhurandhar
