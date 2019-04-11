#include <vector>
using namespace std;

#include "Subject.h"


Subject::Subject(){

}

Subject::~Subject(){

}
void Subject::Attach(PhaseObserver *o){
  observers.push_back(o);
  subjects++;
}

void Subject::notifyObserver(){
      for (PhaseObserver* o : observers)
        o->update();
}
