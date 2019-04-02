#ifndef STRATEGY_H
#define STRATEGY_H

class Game;

class Strategy
{
    public:
        virtual void auction(Game& game) = 0;
        virtual ~Strategy();
        virtual Strategy* clone() = 0;
        /* virtual void purchaseResources(Game& game) = 0; */
        /* virtual void pruchaseCities(Game& game) = 0; */
        /* virtual void powerPlants(Game& game) = 0; */
};

class HumanStrategy : public Strategy
{
    public:
        virtual void auction(Game& game);
        virtual ~HumanStrategy();
        virtual HumanStrategy* clone();
        /* virtual void purchaseResources(Game& game); */
        /* virtual void pruchaseCities(Game& game); */
        /* virtual void powerPlants(Game& game); */
};

#endif
