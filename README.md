# Monopoly Game

## Before Starting
Try to maximize the game window to **full screen** for the best visual experience.
![WhatsApp Image 2024-10-01 at 21 54 35](https://github.com/user-attachments/assets/9a543efe-57a9-408a-8548-32f4fc2f6f17)

## How to Run the Game

To compile and run the game, you can use the following commands:

### Build the Project:
- `make` - Compile the game.
- `make run` - Run the compiled game.
- `make clean` - Clean the build files.

## Game Overview

In this Monopoly game, players take turns rolling dice, moving around the board, buying properties, and building houses or hotels. Players can also trade, pay rent, and collect money when passing "Go." The objective is to bankrupt all other players.

## Game Instructions

### Enter the Number of Players:
1. Move your mouse to the **text input bar** located at the bottom of the window.
2. Enter the number of players (between **2 to 8**).
   ![Player Entry](https://github.com/user-attachments/assets/d3a3ae8c-10c2-4e3b-affa-510ba4717f2e)
3. Press **Enter** to confirm.

### Enter Player Names:
1. After entering the number of players, you'll be prompted to enter each player's name.
2. Move your mouse to the **text input bar**, click to focus, and type the name for each player.
3. Press **Enter** after typing each name.

### Rolling the Dice:
- Once all players are added, click the **"Roll Dice"** button to roll the dice for the current player.
   ![Roll Dice](https://github.com/user-attachments/assets/65d731ac-ed8c-4e65-8904-bf0d11671378)
  
### Move the Player:
- After rolling the dice, the current player will move. You can adjust their position by **left-clicking** on the board. Once the correct position is set, press **Enter** to confirm.

### Building Houses:
1. **To build a house** on your street, **move your mouse to the position of the street** where you want to build a house and press the **B** key.
2. You can build houses only if you own all the properties of a color group.
3. You must build houses **evenly** across all streets in the color group (e.g., you cannot have 3 houses on one street and 1 on another).
4. Each house is represented by a small square in the player's token color.

### Building Hotels:
1. **To build a hotel**, **move your mouse to the street position** where you want to build and press the **H** key.
2. A hotel can only be built if you have 4 houses on all the streets in the same color group.
3. The hotel will be represented by a triangle in the player’s token color.

### Paying Rent and Losing:
- When a player lands on an owned property, they must pay rent. If they cannot afford the rent:
  1. The player can **take a loan** from the bank, which they must repay after passing "Go" three times. If they fail to repay, they lose, and all their properties will be removed from the board.
  2. If they do not take a loan, they **lose** immediately, and their properties will be transferred to the player they owe.
  3. Once a player loses, their token will no longer appear on the board, and their name will be marked with **"(Lost)"**.

### Interacting with the Console:
- The **console** (visible in VS or CLion) will show important game events, such as:
  - The current player's turn.
  - Dice results.
  - Player movements.
  - Houses or hotels built.
  - Any rent payments, loans, or players losing the game.

### Ending the Turn:
- Once you have finished moving and building houses or hotels, press **Enter** to end your turn and move to the next player.

### Game Over:
- The game ends when there is only one player left or when a player reaches a predefined balance (e.g., $5000). The winner's name will be displayed in the console log with **"Game Over"** messages.

## Additional Features:

### House and Hotel Display:
- Houses are displayed as small colored squares on the streets, while hotels are represented by triangles.
- Both houses and hotels will change ownership if the player loses and their properties are transferred to another player.

### Loan Mechanism:
- If a player takes a loan, they must repay it after passing "Go" three times. If they fail to repay it, they will lose, and all their properties will be removed from the board.

### Visuals and Console Log:
- The game uses a **console log** system to keep track of important game actions such as dice rolls, player turns, rent payments, and more.
- This log is updated in real-time as the game progresses.

## Controls Overview:
- **Text Input**: Click on the text bar to type, then press **Enter**.
- **Roll Dice**: Click the **"Roll Dice"** button to roll the dice for the current player.
- **Move Player**: Left-click on the board to move the player after rolling the dice.
- **Build House**: Press **B** to build a house (if conditions are met).
- **Build Hotel**: Press **H** to build a hotel (if conditions are met).
- **End Turn**: Press **Enter** after completing your turn.

---

Enjoy playing Monopoly!
