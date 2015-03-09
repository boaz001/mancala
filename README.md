# mancala [![Build Status](https://travis-ci.org/boaz001/mancala.svg?branch=master)](https://travis-ci.org/boaz001/mancala)
=======

## Game explanation
Mancala is an very old game that is being played all around the world. The rules sometimes differ. This version's rules can be found here: http://boardgames.about.com/cs/mancala/ht/play_mancala.htm

## Goal
This program is part of an assignment for a course on algorithms and data structures (ALGODS).
Therefore two algorithms are implemented to play Mancala against a computer.

## Description
The program is written in C++ and only works as a console application. The board is rewritten after each move. Players enter a move by typing in the pit from where the sowing should start.

Graphical user interface:

```
CPU: 12|11|10|9 |8 |7 |
 -------------------------
 |  |4 |4 |4 |4 |4 |4 |  |
 |0 |--+--+--+--+--+--|0 |
 |  |4 |4 |4 |4 |4 |4 |  |
 -------------------------
HUM: 0 |1 |2 |3 |4 |5 |
HUMAN sow? :
```

## Build and run
```
git clone git@github.com:boaz001/mancala.git && cd mancala
mkdir build && cd build
cmake ..
make
./mancala
```

---
Contributors : Boaz Stolk and Kees Tijsen
