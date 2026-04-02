# Avoid_Bubbles_Game
A simple arcade-style game built with raylib.  Control a red square and dodge incoming enemies from both sides of the screen. Each enemy you avoid increases your score, but the longer you survive, the faster and more unpredictable they become. Test your reflexes and see how long you can last!
🎮 Avoid Bubbles Game

Avoid Bubbles is a simple arcade-style game built using C++ and the raylib library. The objective is to survive as long as possible by avoiding enemies while collecting power-ups to boost your performance.

🕹️ Gameplay
Control your player and avoid incoming enemies.
Gain points over time and by collecting special power-ups.
The game becomes progressively harder as your score increases.
🎯 Features
✅ Smooth player movement
✅ Increasing difficulty based on score
✅ Multiple enemy types:
Normal enemies
Bigger, more dangerous enemies
✅ Power-ups system:
🟢 Points – gain extra score
❤️ Life – gain extra life
⚡ Speed Boost – temporary faster movement
🛡️ Shield – temporary invincibility
✅ Sound effects and background music
✅ Game states:
Start screen
Gameplay
Game over screen
🎮 Controls
Key	Action
⬅️ ➡️ ⬆️ ⬇️	Move player
SPACE	Start game
R	Restart after game over
🛠️ Technologies Used
C++
raylib (graphics, input, audio)
📁 Assets Required

Make sure the following files are in your project directory:

gamemusic.mp3
failsound.mp3
1upsound.mp3
point.png
lifeMushroom.png
speed.png
shield.png
🚀 How to Run
Install raylib
Compile the code with your C++ compiler (example using g++):
g++ main.cpp -o game -lraylib -lopengl32 -lgdi32 -lwinmm
Run the game:
./game
⚙️ Game Mechanics
Enemy speed increases with your score.
Number of enemies scales over time.
Power-ups spawn randomly with different probabilities.
Timers control temporary effects like speed and shield.
📌 Future Improvements
High score saving system
Better UI and animations
More power-up types
Different difficulty levels
