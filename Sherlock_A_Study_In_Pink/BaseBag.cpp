BaseBag::BaseBag() : head(nullptr) {}

BaseItem* BaseBag::get()
{
    object *current = head;
    object *previous = nullptr;
    while(current)
    {
        if((current->item->getType() == MAGIC_BOOK) || (current->item->getType() == ENERGY_DRINK) || (current->item->getType() == FIRST_AID))
        {
            if (previous)
            {
                object *temp = head;
                previous->next = current->next;
                head->next = current->next;
                head = temp->next;
                delete temp;
            }
            else
                head = head->next;
            return current->item;
        }
        previous = current;
        current = current->next;
    }
}

BaseItem* BaseBag::get(ItemType item_type)
{
    object *current = head;
    object *previous = nullptr;
    while (current)
    {
        if (current->item->getType() == item_type)
        {
            if (previous)
            {
                object *temp = head;
                previous->next = head;
                head->next = current->next;
                head = temp->next;
                delete temp;
            }
            else
                head = head->next;
            return current->item;
        }
        previous = current;
        current = current->next;
    }
    return nullptr;
}

string BaseBag::str() const
{
    string result = "Bag[count=" + to_string(num_items) + ";";
    result += enumItemToString(head->item->getType());
    object *current = head->next;
    while (current)
    {
        result = result + "," + enumItemToString(current->item->getType());
        current = current->next;
    }
    result += "]";
    return result;
}

bool SherlockBag::insert(BaseItem *item)
{
    if (num_items < 13)
    {
        object *new_object = new object(item);
        new_object->next = head;
        head = new_object;
        return true;
    }
    return false;        
}

bool WatsonBag::insert(BaseItem *item)
{
    if (num_items < 15)
    {
        object *new_object = new object(item);
        new_object->next = head;
        head = new_object;
        return true;
    }
    return false;        
}
