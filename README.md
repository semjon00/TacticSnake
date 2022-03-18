# TacticSnake
Simple game with unique rules. My pet project that started way back in 2017.

**Build**: Create a folder named `cmake-build` and run `cmake ..` from it.

**Supported platforms**: Windows (tested on Windows 10) and Linux (tested on Manjaro KDE 21.2, launching .exe using wine also works).

**Controls**: WASD and Q. Enter into menus with D.

**How to play the game:**
The game is turn-based, each player takes a turn in their respective order. The player who is unable to make a turn loses. The last standing player wins.

A turn is one of the following:
1) Simple turn: move the head of your snake to cell neighbouring the head (in another words, take the neighbouring cell).
2) Diagonal turn: take a cell diagonally and consume the diagonal boost.
3) Jump turn: take a cell, which is 2 cells away (in a straight way) from the head and consume the jump boost.
4) Knight turn: take a cell one knight-turn away and consume both boosts.

In each turn possibility, the cell previously occupied by a head is getting occupied by a body part.
On the start of the game, each player has one diagonal boost and one jump boost. A player can not make a turn that would consume an already-consumed boost.
A turn can be made by first pressing 'q' (d-1) times, where d is the manhattan distance from the head to the cell to occupy, followed by (d) presses of "wasd" keys.
