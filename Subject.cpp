#include <vector>
using namespace std;

#include "Subject.h"
#include "Observer.h"

Subject::Subject(){
  
}
void Subject::Attach(PhaseObserver *o){
  observers.push_back(o);
  subjects++;
}

void Subject::notifyObserver(){
      for (Observer* o : observers)
        o->update();
}