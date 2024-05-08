class BaseBag
{
protected:
    Character *obj;
    object *head;
    int num_items = 0;
public:
    BaseBag();
    virtual bool insert(BaseItem*) = 0;
    virtual BaseItem* get();
    virtual BaseItem* get(ItemType);
    virtual string str() const;
    int exchangeItem(ItemType);
};

class SherlockBag : public BaseBag
{
private:
    Sherlock *sherlock;
public:
    bool insert(BaseItem*);
};

class WatsonBag : public BaseBag
{
private:
    Watson *watson;
public:
    bool insert(BaseItem*);
};
