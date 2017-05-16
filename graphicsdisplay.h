#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
class Cell;

class GraphicsDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
  Xwindow& theWindow;
  enum status{on, off};
  void update(int r, int c, status s);
  std::string moveMsg(int moves);
  int cellSize;

 public:
  GraphicsDisplay(int n, Xwindow& window);

  void notify(Subject &whoNotified) override;
  SubscriptionType subType() const override;

  ~GraphicsDisplay();

  void display(); 
  void printMove(int moves);
};

#endif

