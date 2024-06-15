# Snake-Game-OOP-C++
My 2nd semester project of Object oriented programming
Animated Snake Game
This project is a classic Snake game implemented in C++. It was developed as part of a third-semester OOP (Object-Oriented Programming) course. The game features a graphical representation in the console using ASCII characters and offers basic functionalities such as moving the snake, growing the snake when it eats food, and detecting collisions.

Features
Player Input: Users can input their name, which is displayed during the game.
Dynamic Snake Movement: The snake can move in four directions using the w, a, s, and d keys.
Food Generation: Food is generated at random positions within the game boundaries.
Collision Detection: The game detects collisions with the boundaries and the snake's own body.
Score Tracking: The game keeps track of the player’s score, which increases when the snake eats food.
Game Over Screen: The game ends when the snake collides with itself or the boundaries, displaying a game-over message.
How to Play
Start the Game: Compile and run the program. You will be prompted to enter your name.
Control the Snake: Use the w, a, s, and d keys to move the snake up, left, down, and right respectively.
Eat Food: Navigate the snake to the food to increase its length and your score.
Avoid Collisions: Do not run into the walls or the snake’s own body.
Implementation Details
Classes and Objects: The game is encapsulated within a SnakeGame class, utilizing private and public members to manage the game state.
Game Loop: The game runs in a loop, checking for user input, updating the snake’s position, drawing the game state, and checking for collisions.
Console Graphics: The game uses console-specific functions to draw the game state, minimizing flicker and providing a smoother visual experience.
Random Food Placement: The food position is randomly generated, ensuring it does not overlap with the snake's body.
