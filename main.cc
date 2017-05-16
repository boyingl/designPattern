#include <iostream>
#include <string>
#include "grid.h"
#include "window.h"
using namespace std;



int main() {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd, aux;
  Grid g;
  int moves = 0;
  Xwindow window{};
  // You will need to make changes to this code.

  try {
    while (true) {
      cin >> cmd;
      if (cmd == "new") {
        int n;
        cin >> n;
        //initialize a new grid
        g.init(n, window);
      }
      else if (cmd == "init") {
        int row, col;
        while(cin >> row >> col){
          //if not end of initial configuration, initialize the cell
          if(row != -1 && col != -1) g.init(row,col);
          else break;
        }
        g.display();
      }
      else if (cmd == "game") {
        cin >> moves;
        g.printMove(moves);
      }
      else if (cmd == "switch") {
        int r = 0, c = 0;
        cin >> r >> c;
        //toggle will in turn update the graphics display
        g.toggle(r, c);
        moves -- ;
        g.printMove(moves);

        if(g.isWon()){
          cout << "Won" << endl;
          return 0;
        }
        if(moves == 0){
          cout << "Lost" << endl;
          return 0;
        }
      }
    }
  }
  catch (ios::failure &) {
  }
}


