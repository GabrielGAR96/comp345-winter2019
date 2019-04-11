#pragma once

#include <vector>
using namespace std;

#include "Observer.h"
#include "PhaseObserver.h"
class Subject{

private:

  vector<Observer*> observers;
  int subjects;
public:
  Subject();
  ~Subject();
  void Attach(PhaseObserver *obs);
  //virtual void Detatch(Observer* obs);
  void notifyObserver();

};
