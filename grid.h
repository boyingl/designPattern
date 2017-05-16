#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "cell.h"
#include "graphicsdisplay.h"
#include "window.h"

class Grid {
  std::vector<std::vector<Cell*>> theGrid;  // The actual grid.
  int gridSize;    // Size of the grid.
  GraphicsDisplay *gd; // The text display.
  //if a Grid is initially configured or not
  bool initialized;
  void clearGrid();   // Frees the grid.

 public:
  Grid();
  ~Grid();
  
  bool isWon() const; // Call to determine if grid is in a winning state.
  void init(int n, Xwindow& window); // Sets up an n x n grid.  Clears old grid, if necessary.
  void turnOn(int r, int c);  // Sets cell at row r, col c to On.
  void toggle(int r, int c);  // Switches cell at (r, c) between On and Off.
  void init(int r, int c);
  //display the graphics grid
  void display();
  //display having #moves move left
  void printMove(int moves);
};

#endif

