#include <iostream>
#include <sstream>
#include <utility>
#include "graphicsdisplay.h"
#include "cell.h"
#include "info.h"
#include "subscriptions.h"
#include "window.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int n, Xwindow& theWindow): gridSize{n}, theWindow{theWindow}{
  //cell is evenly distributed, with 2 seperation line between each row & col 
	cellSize = (450 - 2*(gridSize-1))/gridSize;
	theDisplay = vector<vector<char> >(gridSize);
	for(int i = 0; i < gridSize; i++){
		theDisplay[i] = vector<char>(gridSize);
		for(int j = 0; j < gridSize; j++){
			theDisplay[i][j] = '_';
		}
	}
}


void GraphicsDisplay::notify(Subject &whoNotified) {
	Info info = whoNotified.getInfo();
	int row = info.row;
	int col = info.col;
	if(info.state) {
		theDisplay[row][col] = 'X';
		update(row, col, on);
	}
	else {
		theDisplay[row][col] = '_';		
		update(row, col, off);
	}
}


GraphicsDisplay::~GraphicsDisplay() {}


SubscriptionType GraphicsDisplay::subType() const {
	return SubscriptionType::All;
}


//display according to the data in theDisplay, add seperation line between each cell for clarity
void GraphicsDisplay::display(){
	
	for(int i = 0; i < gridSize; i++){
		for(int j = 0; j < gridSize; j ++){

			int x = (cellSize +2 )*j + 25;
			int y = (cellSize +2 )*i + 25;

			if(theDisplay[i][j] == 'X') theWindow.fillRectangle(x, y , cellSize, cellSize, Xwindow::White);
			//off, black
			else theWindow.fillRectangle(x, y , cellSize, cellSize, Xwindow::Black);
		}		
	}
}


//upate a graphics cell
void GraphicsDisplay::update(int r, int c, status s){
	int x = (cellSize +2 )*c + 25;
	int y = (cellSize +2 )*r + 25;
	int color;
	if(s == status::on) color = 0;
	else color = 1;
	theWindow.fillRectangle(x, y , cellSize, cellSize, color);
}


string GraphicsDisplay::moveMsg(int moves){
	string msg = "moves";
	if(moves == 1) msg = "move";
	ostringstream moveStream;
	moveStream << moves;

	msg = moveStream.str() + "   " + msg + "   left" ;
	return msg;
}


void GraphicsDisplay::printMove(int moves){
  theWindow.fillRectangle(0, 0 , 500, 50, Xwindow::White);
	string msg = moveMsg(moves);
	theWindow.drawString(200, 10, msg, Xwindow::Red);
}



