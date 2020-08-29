#ifndef MERCHANT_H
#define MERCHANT_H

class Unit;
class Backpack;

//------------------------------------------------------------------------------
// class Merchant: child class of class Unit
//------------------------------------------------------------------------------
class Merchant : public Unit {
protected:
    Backpack *itemsToSell;
    Backpack *itemsBought;
    
public:
    Merchant();
    Merchant(int numItemsToSell);
    virtual ~Merchant();

    // helper functions(general)   
    void initMerchant(int numItemsToSell);
    void destroyMerchant();

    void initItemsToSell(int numItemsToSell);
    void destroyItemsToSell();
    
    void initItemsBought();
    void destroyItemsBought();
    
    bool isMerchant();
    
    virtual void interact(Unit *unit);
    
    void buy(Unit *unit);
    void sell(Unit *unit);
    
    virtual void move(int moveDir);
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
