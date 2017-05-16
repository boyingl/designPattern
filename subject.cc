#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
#include <iostream>
using namespace std;

//add o as an observer
void Subject::attach(Observer *o) { 
  observers.push_back(o);
}


void Subject::notifyObservers(SubscriptionType t) {
	//if notify SwitchOnly <=> notify everyone
  if(t == SubscriptionType::SwitchOnly){
	  for(auto& ob: observers) ob->notify(*this);
  }

  //notify All only notifies All type subscription
  else{
    for(auto& ob: observers){
      SubscriptionType obType = ob->subType();
      if(obType == SubscriptionType::All)  ob->notify(*this);
    }
  }
}


Subject::~Subject(){ }


