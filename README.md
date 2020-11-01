# Dungeon-Explorer
Dungeon Explorer is a multiplayer side-scrolling video game designed for the ATMega1284p microcontroller. Dungeon Explorer was developed during Winter Quarter 2017 at the University of California, Riverside.

## Design
See "Project Report.pdf" for information on the physical design of the project and program logic. 

## Gameplay
Upon powering on the project, the title screen of the game will be displayed, telling players to "Press Start" to continue. After pressing the Start button, players will be given the option to either start a new game, or to continue from a saved game. If starting a new game, the players will begin in the first level of the dungeon and must travel left-to-right to reach the door at the other end. Player 1 and Player 2 can move and attack independently of one another. Enemies will spawn offscreen and move towards the players, who can attack them. The enemies can also attack the players, which will lower their health. If either player's health drops to zero, the game will end. Upon reaching the door, the players are given the option to save their progress using the microcontroller's EEPROM. The game can be paused by either player during gameplay. While paused, the players can choose to resume their game, or to quit to the main menu. If the players make it through three levels of the dungeon, they will win the game and be returned to the main menu. 
