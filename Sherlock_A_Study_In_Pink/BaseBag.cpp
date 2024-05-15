#include "BaseBag.h"

BaseBag::BaseBag(Character* character) : character(character), items_count(0)
{
    for (int i = 0; i < 15; ++i)
        items[i] = NULL;
}
bool BaseBag::insert(BaseItem* item)
{
    if (items_count < 15)
    {
        addToHead(*this, item);
        return true;
    }
    return false;
}
BaseItem* BaseBag::get()
{
    for (int i = 0; i < items_count; ++i)
    {
        if (items[i]->canUse(character, NULL) && (items[i]->getItemType() == MAGIC_BOOK || items[i]->getItemType() == ENERGY_DRINK || items[i]->getItemType() == FIRST_AID))
        {
            BaseItem* takeOutItem = items[i];

            // Swap takeOutItem with head item
            if (i > 0)
            {
                items[i] = items[0];
                items[0] = takeOutItem;
            }

            // Remove head item
            deleteItemFromHead(*this);
            return takeOutItem;
        }
    }
    return NULL;
}
BaseItem* BaseBag::get(ItemType item_type)
{
    for (int i = 0; i < items_count; ++i)
    {
        if (items[i]->canUse(character, NULL) && (items[i]->getItemType() == item_type))
        {
            BaseItem* takeOutItem = items[i];

            // Swap takeOutItem with head item
            if (i > 0)
            {
                items[i] = items[0];
                items[0] = takeOutItem;
            }

            // Remove head item
            deleteItemFromHead(*this);
            return takeOutItem;
        }
    }
    return NULL;
}
string BaseBag::str() const
{
    string result;
    if (items_count != 0)
    {
        result = "BaseBag[count=" + to_string(items_count) + ";";
        for (int i = 0; i < items_count; ++i)
        {
            result += ToString(items[i]->getItemType());

            if (i < items_count - 1)
                result += ",";
        }
        result += "]";
    }
    else
        result = "BaseBag[count=0]";
    return result;
}

SherlockBag::SherlockBag(Sherlock* sherlock) : BaseBag(sherlock) {}
BaseItem* SherlockBag::get()
{
    for (int i = 0; i < items_count; ++i)
    {
        if (items[i]->canUse(character, NULL) && (items[i]->getItemType() == MAGIC_BOOK || items[i]->getItemType() == ENERGY_DRINK || items[i]->getItemType() == FIRST_AID))
        {
            BaseItem* takeOutItem = items[i];

            // Swap takeOutItem with head item
            if (i > 0)
            {
                items[i] = items[0];
                items[0] = takeOutItem;
            }

            // Remove head item
            deleteItemFromHead(*this);
            return takeOutItem;
        }
    }
    return NULL;
}
BaseItem* SherlockBag::get(ItemType item_type)
{
    for (int i = 0; i < items_count; ++i)
    {
        if (items[i]->canUse(character, NULL) && (items[i]->getItemType() == item_type))
        {
            BaseItem* takeOutItem = items[i];

            // Swap takeOutItem with head item
            if (i > 0)
            {
                items[i] = items[0];
                items[0] = takeOutItem;
            }

            // Remove head item
            deleteItemFromHead(*this);
            return takeOutItem;
        }
    }
    return NULL;
}
bool SherlockBag::insert(BaseItem* item)
{
    if (this->items_count < SHERLOCK_BAG_MAX_ITEM)
    {
        addToHead(*this, item);
        return true;
    }
    return false;
}

WatsonBag::WatsonBag(Watson* watson) : BaseBag(watson) {}
BaseItem* WatsonBag::get()
{
    for (int i = 0; i < items_count; ++i)
    {
        if (items[i]->canUse(character, NULL) && (items[i]->getItemType() == MAGIC_BOOK || items[i]->getItemType() == ENERGY_DRINK || items[i]->getItemType() == FIRST_AID))
        {
            BaseItem* takeOutItem = items[i];

            // Swap takeOutItem with head item
            if (i > 0)
            {
                items[i] = items[0];
                items[0] = takeOutItem;
            }

            // Remove head item
            deleteItemFromHead(*this);
            return takeOutItem;
        }
    }
    return NULL;
}
BaseItem* WatsonBag::get(ItemType item_type)
{
    for (int i = 0; i < items_count; ++i)
    {
        if (items[i]->canUse(character, NULL) && (items[i]->getItemType() == item_type))
        {
            BaseItem* takeOutItem = items[i];

            // Swap takeOutItem with head item
            if (i > 0)
            {
                items[i] = items[0];
                items[0] = takeOutItem;
            }

            // Remove head item
            deleteItemFromHead(*this);
            return takeOutItem;
        }
    }
    return NULL;
}
bool WatsonBag::insert(BaseItem* item)
{
    if (this->items_count < WATSON_BAG_MAX_ITEM)
    {
        addToHead(*this, item);
        return true;
    }
    return false;
}