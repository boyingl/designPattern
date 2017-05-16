#include <iostream>
#include "grid.h"
#include "cell.h"
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
using namespace std;

Grid::Grid(): gd{nullptr}, initialized{false} { }


Grid::~Grid() { clearGrid(); }


void Grid::clearGrid() {
	//if the grid not configured, return
	if(! initialized ) return;

  //free graphics display
	if(gd) 	delete gd;
	//free each cell
	for(int i = 0; i < gridSize; i++){
		for(int j = 0; j < gridSize; j++){  delete theGrid[i][j]; }
	}
	
	initialized = false;
}


bool Grid::isWon() const {
	//check each cell, if anyone is on, then not won
	for(int i = 0; i < gridSize; i++){
		for(int j = 0; j < gridSize; j++){
			if(theGrid[i][j]->getState()) return false;
		}
	}
	return true;
}


void Grid::init(int n, Xwindow& window) {
	clearGrid();
	gd = new GraphicsDisplay(n, window);
	gridSize = n;
	theGrid = vector<vector<Cell*>>(gridSize);
	for(int i = 0; i < gridSize; i++){
		theGrid[i] = vector<Cell*>(gridSize);
		for(int j = 0; j < gridSize; j++){
			//create a new cell & give coordinates
			theGrid[i][j] = new Cell{};
			theGrid[i][j]->setCoords(i, j);
			//add gd as subscriber to the cell
			theGrid[i][j]->attach(gd);		
		}
	}

	//add neighbour as observers if the neighbour exists
	for(int i = 0; i < gridSize; i++){
		for(int j = 0; j < gridSize; j++){
			if( (i-1) >= 0)  	theGrid[i][j]->attach(theGrid[i-1][j]);			
			if( (j+1) < gridSize ) 	theGrid[i][j]->attach(theGrid[i][j+1]);		
			if( (i+1) < gridSize )  theGrid[i][j]->attach(theGrid[i+1][j]);			
			if( (j-1) >= 0 ) 	theGrid[i][j]->attach(theGrid[i][j-1]);		
		}
	}
	initialized = true;
}


void Grid::turnOn(int r, int c) {
	theGrid[r][c]->setOn();
}


//switch command from user, notify neighbors also
void Grid::toggle(int r, int c) {
	theGrid[r][c]->toggle();
	theGrid[r][c]->notifyObservers(SubscriptionType::SwitchOnly);
}


//notify textdisplay only
void Grid::init(int r, int c) {
	theGrid[r][c]->setOn();
	theGrid[r][c]->notifyObservers(SubscriptionType::All);
}


//display the graphics grid
void Grid::display(){
	gd->display();
}


//display having #moves move left
void Grid::printMove(int moves){
	gd->printMove(moves);
}


