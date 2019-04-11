#pragma once

class Observer{
  private:

  public:

    Observer();
    virtual ~Observer();
    virtual void update()= 0;
};
