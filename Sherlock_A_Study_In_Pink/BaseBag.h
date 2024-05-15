#pragma once
#ifndef _BASE_BAG
#include "movingObject.h"
#include "thuvien.h"
#include "baseItem.h"
#define SHERLOCK_BAG_MAX_ITEM 13
#define WATSON_BAG_MAX_ITEM 15
class BaseBag
{
protected:
    Character* character;

    BaseItem* items[15];
    int items_count;

    void addToHead(BaseBag& baseBag, BaseItem* itemToAdd)
    {
        if (baseBag.items_count == 0)
        {
            baseBag.items[0] = itemToAdd;
            items_count++;
        }
        else
        {
            for(int i = baseBag.items_count; i > 0; --i)
                baseBag.items[i] = baseBag.items[i - 1];
            baseBag.items_count++;
            baseBag.items[0] = itemToAdd;
        }
    }
    void deleteItemFromHead(BaseBag& baseBag)
    {
        for (int i = 0; i < baseBag.items_count - 1; ++i)
            baseBag.items[i] = baseBag.items[i + 1];
        baseBag.items[baseBag.items_count - 1] = nullptr;
        baseBag.items_count--;
    }
    const char* ToString(ItemType item) const
    {
        switch (item)
        {
        case MAGIC_BOOK:   
            return "MagicBook";
        case ENERGY_DRINK:   
            return "EnergyDrink";
        case FIRST_AID: 
            return "FirstAid";
        case EXCEMPTION_CARD: 
            return "ExcemptionCard";
        case PASSING_CARD: 
            return "PassingCard";
        default:      
            return "[Unknown OS_type]";
        }
    }
public:
    BaseBag(Character*);
    virtual bool insert(BaseItem*);
    virtual BaseItem* get();
    virtual BaseItem* get(ItemType);
    virtual string str() const;

    //int exchangeItem(ItemType);
};

class SherlockBag : public BaseBag
{
public:
    SherlockBag(Sherlock*);
    
    // Process of giving item to Watson if both met
    BaseItem* get();
    BaseItem* get(ItemType);
    bool insert(BaseItem*);
};

class WatsonBag : public BaseBag
{
public:
    WatsonBag(Watson*);

    // Process of giving item to Sherlock if both met
    BaseItem* get();
    BaseItem* get(ItemType);
    bool insert(BaseItem*);
};

//struct NodeItem
//{
//    BaseItem* item;
//    NodeItem* next;
//};
//
//class BaseBag
//{
//    friend class TestStudyInPink;
//    const char* ToString(ItemType item) const
//    {
//        switch (item)
//        {
//        case MAGIC_BOOK:   
//            return "MagicBook";
//        case ENERGY_DRINK:   
//            return "EnergyDrink";
//        case FIRST_AID: 
//            return "FirstAid";
//        case EXCEMPTION_CARD: 
//            return "ExcemptionCard";
//        case PASSING_CARD: 
//            return "PassingCard";
//        default:      
//            return "[Unknown OS_type]";
//        }
//    }
//public:
//    int capacity;
//    int count;
//    Character* obj;
//    NodeItem* head;
//public:
//    virtual bool insert(BaseItem*) = 0;
//    virtual BaseItem* get() = 0;
//    virtual BaseItem* get(ItemType) = 0;
//    virtual string str() const;
//};
//
//class SherlockBag : public BaseBag
//{
//    friend class TestStudyInPink;
//public:
//    SherlockBag(Sherlock*);
//    bool insert(BaseItem*);
//    BaseItem* get();
//    BaseItem* get(ItemType);
//};
//
//class WatsonBag : public BaseBag
//{
//    friend class TestStudyInPink;
//public:
//    WatsonBag(Watson*);
//    bool insert(BaseItem*);
//    BaseItem* get();
//    BaseItem* get(ItemType);
//};
#endif // !_BASE_BAG