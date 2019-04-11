#pragma once

#include <vector>
using namespace std;

#include "Observer.h"

class Subject{

private:

  vector<Observer*> observers;
  int subjects;
public:
  Subject();
  ~Subject();
  void Attach(Observer* obs);
  //virtual void Detatch(Observer* obs);
  void notifyObserver();

};
