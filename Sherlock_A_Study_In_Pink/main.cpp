#include "thuvien.h"
#include "configuration.h"
#include "position.h"
#include "movingObject.h"
#include "map.h"
#include "arrayMovingObject.h"
#include "BaseBag.h"


int main()
{
    int num_walls = 3;
    Position arr_walls[] = { Position(1, 2), Position(2, 3), Position(3, 4) };
    int num_fake_walls = 1;
    Position arr_fake_walls[] = { Position(2, 0) };

    Map* map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock* sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 101, 150);

    BaseItem* magicBook = new MagicBook();
    BaseItem* energyDrink = new EnergyDrink();
    BaseItem* firstAid = new FirstAid();
    BaseItem* excemptionCard = new ExcemptionCard();
    BaseItem* passingCard = new PassingCard("RobotS");

    BaseBag* sherlockBag = new SherlockBag(sherlock);
    sherlockBag->insert(magicBook);
    sherlockBag->insert(energyDrink);
    sherlockBag->insert(firstAid);
    sherlockBag->insert(energyDrink);
    sherlockBag->insert(excemptionCard);
    sherlockBag->insert(passingCard);
    sherlockBag->insert(firstAid);
    sherlockBag->insert(excemptionCard);
    cout << sherlockBag->str() << endl; // Test insert()
    // ________________________________
    // Test get()
    // sherlockBag->get();
    // cout << sherlockBag->str() << endl;
    // sherlockBag->get();
    // cout << sherlockBag->str() << endl;    
    // sherlockBag->get();
    // cout << sherlockBag->str() << endl;
    // sherlockBag->get();
    // cout << sherlockBag->str() << endl;

    // ________________________________
    // Test get(ItemType)
    // sherlockBag->get(MAGIC_BOOK);
    // cout << sherlockBag->str() << endl;
    // sherlockBag->get(EXCEMPTION_CARD);
    // cout << sherlockBag->str() << endl;

    return 0;
}