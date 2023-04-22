# OthelloGameSolver
Artificial Intelligence which solves Othello Game 

This repository contains C++ implementation of an AI Othello game solver. This project handles the idea of the Artificial Intelligence (AI) which plays the game called "Othello" against "Human Users", or against other AIs. I used search trees and traverse tree-based structures with implementing complex recursive algorithm.


Usage:
The program will display a graphical user interface (GUI) of the Othello game board. The AI player will always be black, and the user can play as white.

![OthelloUI_Startup1](https://user-images.githubusercontent.com/104103767/233768954-19d4e82f-8e51-4770-bc8b-a7817ed9419a.png)
![OthelloUI_Game2](https://user-images.githubusercontent.com/104103767/233768964-8ebeed9c-e670-42bd-bbef-9630d2ba1b31.png)


How to Play
Click on an empty square to place a white disc.
The AI player will then make its move and place a black disc on the board.
Continue playing in turns until the game is over.
The game will end when either all the squares on the board are filled, or no valid moves are left for either player. The winner is the player with the most discs on the board at the end of the game.

Algorithm
The program uses a heuristic algorithm to search for the best move for the AI player. The algorithm evaluates the possible moves based on several criteria, such as the number of discs that will be flipped, the stability of the discs, and the position of the discs on the board. The algorithm then assigns a score to each possible move, and selects the move with the highest score as the best move for the AI player.

![SearchTree3](https://user-images.githubusercontent.com/104103767/233768987-8b241d93-2c63-4897-975a-48271a30592b.jpeg)
