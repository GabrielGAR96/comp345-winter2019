#pragma once

#include <vector>
using namespace std;


#include "PhaseObserver.h"
class Subject{

private:

  vector<PhaseObserver*> observers;
  int subjects;
public:
  Subject();
  ~Subject();
  void Attach(PhaseObserver *obs);
  //virtual void Detatch(Observer* obs);z
  void notifyObserver();

};
