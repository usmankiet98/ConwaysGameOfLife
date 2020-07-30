# HCI 104497: Conway Game of Life - An OS course project #
### PROJECT MEMBERS ###
Student ID | Name
------------ | -------------
**63669** | **SABAHAT KHAN**
63626 | Syed Muhammad Usman


## Approach ##
First we implement our own concepts, then we use internet & a website I remember https://www.geeksforgeeks.org/, https://stackoverflow.com/, https://www.quora.com/, https://www.reddit.com/

## Problems Faces ##

### Problem 1: C Language was very new for both of us ###
Understading of C was for not much easy.

### Problem 2: Ubantu ###
Installation and using Ubantu was not much easy.

### Problem 3: GitHub ###
Using github was first experience, to invite, receive and commit code.

## References ##
-https://www.geeksforgeeks.org/
-https://stackoverflow.com/
-https://www.quora.com/
-https://www.reddit.com/
# REPORT #
# OPERATING SYSTEM PROJECT #
# CONWAY’S GAME OF LIFE #

## INTRODUCTION: ##

### 1.1 Purpose ###
•	The project has been made for Operating System’s Semester Final Project.

### 1.2 Document convention: ###
•	Calibri (Body) used.
•	Main features or important terms are in bold.

### 1.3 Project Scope: ###
It’s a game named Game of Life It is a 'cellular automaton', and was invented by Cambridge mathematician John Conway.
It’s a well-known game, it’s a collection of cells, based on mathematical functions, can live, die, multiply. 

### 1.4 Team Players: ###
•	Sabahat (63669)
•	Syed Muhammad Usman (63626)

### 1.5 Technology Used: ###
•	C language on UBUNTU

### Classes: ###
•	Cyclic Barrier
•	Board Splitter


### Libraries: ###
•	Pthread
•	Cyclic barrier

### Specifications: ###
### Rules ###
It’s a two dimensional orthogonal grid of cells square shaped, each of them have two possible states, live or die, each of them interacts with its eight neighbors, on every step the following transitions occurs:
•	Any live cell with fewer than two live neighbours dies, as if by underpopulation.
•	Any live cell with two or three live neighbours lives on to the next generation.
•	Any live cell with more than three live neighbours dies, as if by overpopulation.
•	Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

These rules, which compare the behaviour of the automaton to real life, can be condensed into the following:
•	Any live cell with two or three live neighbours survives.
•	Any dead cell with three live neighbours becomes a live cell.
•	All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations.
