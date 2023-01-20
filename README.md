# Project-Minesweeper
### Course project Minesweeper, created by me for my UP course @ FMI, Sofia University.

**A simple implementation of the popular game Мinesweeper, written in C++.**

**Purpose of the game:** to reveal all positions in a given square matrix that are not marked as mined without revealing any of the mines first.
The user wins if all mines are marked and loses if any mine is opened.

**Functionality:**
1. The user must choose valid size of the matrix field (from 3 to 10) and valid number of mines (from 1 to 3*size of the field) to be hidden in order to start playing. If the data is not valid, then the user is asked to enter it again;
2. Then the user should type a valid command and coordinates of a cell form the field. Again, if any of the given data is invalid, the user will be asked to enter it again.
3. 
* *Note:* Valid commands are:
 - **_open_** (If there is a mine there - game over);
 - **_mark_** (Marks the cell as a ‘mine’);
 - **_unmark_** (Unmarks the cell so it is not marked as a ‘mine’ anymore).
