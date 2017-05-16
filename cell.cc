#include <utility>
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include "subscriptions.h"
#include "info.h"

using namespace std;

Cell::Cell(): isOn{false} {}


bool Cell::getState() const { return isOn; }


//get status & coordinate of the cell
Info Cell::getInfo() const {
	Info info;
	info.state = isOn;
	info.row = r;
	info.col = c;
	return info;
}


void Cell::setOn() { 
	isOn = true;
}


void Cell::toggle() {
	if(isOn) isOn = false;
	else isOn = true;
}


void Cell::setCoords(int r, int c) { this->r = r; this->c = c; }


//when the subject of the cell updates
//cell toggle & notify the graphics display
void Cell::notify(Subject & whoNotified) {
	toggle();
	notifyObservers(SubscriptionType::All);
}


//a cell subscribe to its neighbours as SwitchOnly
SubscriptionType Cell::subType() const {   
	return SubscriptionType::SwitchOnly; 
}


Cell::~Cell(){}


