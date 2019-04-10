#ifndef STRATEGY_H
#define STRATEGY_H

class Game;

class Strategy
{
    public:
        virtual void auction(Game& game) = 0;
        virtual ~Strategy();
        virtual Strategy* clone() = 0;
        virtual bool purchaseResources(Game& game) = 0;
        virtual bool purchaseCities(Game& game) = 0;
};

class HumanStrategy : public Strategy
{
    public:
        virtual void auction(Game& game);
        virtual ~HumanStrategy();
        virtual HumanStrategy* clone();
        virtual bool purchaseResources(Game& game);
        virtual bool purchaseCities(Game& game);
};

#endif
