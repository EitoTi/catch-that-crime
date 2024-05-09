#include "StudyInPinkProgram.h"

int getDistance(Position pos1, Position pos2)
{
    return (abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol()));
}

int findMainNum(int n)
{
    int sum = 0;
    while ((n > 0) || (sum > 9))
    {
        if (n == 0)
        {
            n = sum;
            sum = 0;
        }
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
StudyInPinkProgram::StudyInPinkProgram(const string &config_file_path)
{
    config = new Configuration(config_file_path);
    map = new Map(this->config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    sherlock_bag = new SherlockBag(sherlock);
    watson_bag = new WatsonBag(watson);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
}

StudyInPinkProgram::~StudyInPinkProgram()
{
    delete arr_mv_objs;
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
    delete config;
    delete sherlock_bag;
    delete watson_bag;
}

bool StudyInPinkProgram::isStop() const
{
    if ((sherlock->getHp() == 0) || (watson->getHp() == 0) || sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()) || watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()))
        return true;
    return false;
}

void StudyInPinkProgram::printResult() const
{
    if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()))
        cout << "Sherlock caught the criminal" << endl;
    else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()))
        cout << "Watson caught the criminal" << endl;
    else
        cout << "The criminal escaped" << endl;
}

void StudyInPinkProgram::printStep(int si) const
{
    cout << "Step: " << setw(4) << setfill('0') << si << "--" << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
}

void StudyInPinkProgram::run(bool verbose)
{
    for (int i = 0; i < config->num_steps; i++)
    {
        for (int j = 0; j < arr_mv_objs->getCount(); j++)
        {
            MovingObject *obj = arr_mv_objs->getMovingObectAtPosition(j);
            obj->move();
            if (obj->getName() == "Criminal")
            {
                if (criminal->getCriminalNumSteps() == 3)
                {
                    Position criminal_pre_pos = criminal->getPreviousPosition();
                    Robot *robot = nullptr;
                    BaseItem *item = nullptr;
                    if (Robot::isFirstRobot())
                    {
                        robot = new RobotC(arr_mv_objs->getCount() + 1, criminal_pre_pos, map, criminal);
                        Robot::setFirstRobot(false);
                    }
                    else
                    {
                        int distance_to_sherlock = getDistance(criminal_pre_pos, sherlock->getCurrentPosition());
                        int distance_to_watson = getDistance(criminal_pre_pos, watson->getCurrentPosition());
                        if (distance_to_sherlock < distance_to_watson)
                            robot = new RobotS(arr_mv_objs->getCount() + 1, criminal_pre_pos, map, criminal, sherlock);
                        else if (distance_to_sherlock > distance_to_watson)
                            robot = new RobotW(arr_mv_objs->getCount() + 1, criminal_pre_pos, map, criminal, watson);
                        else if (distance_to_sherlock == distance_to_watson)
                            robot = new RobotSW(arr_mv_objs->getCount() + 1, criminal_pre_pos, map, criminal, sherlock, watson);
                    }
                    int n = findMainNum(criminal_pre_pos.getRow() * criminal_pre_pos.getCol());
                    if ((n >= 0) && (n <= 1))
                        item = new MagicBook();
                    else if ((n >= 2) && (n <= 3))
                        item = new EnergyDrink();
                    else if ((n >= 4) && (n <= 5))
                        item = new FirstAid();
                    else if ((n >= 6) && (n <= 7))
                        item = new ExcemptionCard();
                    else if ((n >= 8) && (n <= 9))
                    {
                        string challenge;
                        int t = (criminal_pre_pos.getRow() * 11 + criminal_pre_pos.getCol()) % 4;
                        switch (t)
                        {
                            case 0: 
                                challenge = "RobotS";
                                break;
                            case 1: 
                                challenge = "RobotC";
                                break;
                            case 2:
                                challenge = "RobotSW";
                                break;
                            case 3:
                                challenge = "all";
                                break;
                        }
                        item = new PassingCard(challenge);
                    }
                    arr_mv_objs->add(robot);
                    robot->setItem(item);
                    criminal->setCriminalNumSteps(0);
                }
            }
            else if (obj->getName() == "Sherlock")
            {
                if (sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition().getRow(), watson->getCurrentPosition().getCol()))
                {
                    cout << "Meet";
                    BaseItem *exchange_item = sherlock_bag->get(PASSING_CARD);
                    while(exchange_item)
                    {
                        watson_bag->insert(exchange_item);
                        exchange_item = sherlock_bag->get(PASSING_CARD);
                    }
                    exchange_item = watson_bag->get(EXCEMPTION_CARD);
                    while(exchange_item)
                    {
                        sherlock_bag->insert(exchange_item);
                        exchange_item = watson_bag->get(EXCEMPTION_CARD);
                    }
                    cout << "Done";
                }
                for (int k = 3; k < arr_mv_objs->getCount(); k++)
                {
                    if (sherlock->getCurrentPosition().isEqual(arr_mv_objs->getMovingObectAtPosition(k)->getCurrentPosition().getRow(), arr_mv_objs->getMovingObectAtPosition(k)->getCurrentPosition().getCol()))
                    {
                        Robot *robot = (Robot*)arr_mv_objs->getMovingObectAtPosition(k);
                        if (sherlock_bag->get(EXCEMPTION_CARD))
                            if (sherlock_bag->get(EXCEMPTION_CARD)->canUse(sherlock, robot))
                                sherlock->noModifyCharacterStats = true;
                        if (robot->getName() == "RobotS")
                        {
                            if (sherlock->getExp() > 400)
                                sherlock_bag->insert(robot->getItem());
                            else
                                if (!sherlock->noModifyCharacterStats)
                                    sherlock->setExp(sherlock->getExp() * 0.9);
                        }
                        else if (robot->getName() == "RobotW")
                            sherlock_bag->insert(robot->getItem());
                        else if (robot->getName() == "RobotSW")
                        {
                            if ((sherlock->getHp() > 335) && (sherlock->getExp() > 300))
                                sherlock_bag->insert(robot->getItem());
                            else
                                if (!sherlock->noModifyCharacterStats)
                                {
                                    sherlock->setHp(sherlock->getHp() * 0.85);
                                    sherlock->setExp(sherlock->getExp() * 0.85);
                                }
                        }
                        else if (robot->getName() == "RobotC")
                        {
                            if (sherlock->getExp() > 500)
                            ;
                            else
                                sherlock_bag->insert(robot->getItem());
                        }
                        BaseItem *item = sherlock_bag->get();
                        if (item)
                            if (item->canUse(sherlock, robot))
                                item->use(sherlock, robot);
                        sherlock->roundHp();
                        sherlock->roundExp();
                        sherlock->noModifyCharacterStats = false;
                    }
                }
            }
            else if (obj->getName() == "Watson")
            {
                if (watson->getCurrentPosition().isEqual(sherlock->getCurrentPosition().getRow(), sherlock->getCurrentPosition().getCol()))
                {
                    BaseItem *exchange_item = watson_bag->get(EXCEMPTION_CARD);
                    while(exchange_item)
                    {
                        sherlock_bag->insert(exchange_item);
                        exchange_item = watson_bag->get(EXCEMPTION_CARD);
                    }
                    exchange_item = sherlock_bag->get(PASSING_CARD);
                    while(exchange_item)
                    {
                        watson_bag->insert(exchange_item);
                        exchange_item = sherlock_bag->get(PASSING_CARD);
                    }
                }
                for (int k = 3; k < arr_mv_objs->getCount(); k++)
                {
                    if (watson->getCurrentPosition().isEqual(arr_mv_objs->getMovingObectAtPosition(k)->getCurrentPosition().getRow(), arr_mv_objs->getMovingObectAtPosition(k)->getCurrentPosition().getCol()))
                    {
                        Robot *robot = (Robot*)arr_mv_objs->getMovingObectAtPosition(k);
                        if (watson_bag->get(PASSING_CARD))
                            if (watson_bag->get(PASSING_CARD)->canUse(watson, robot))
                                watson_bag->get(PASSING_CARD)->use(watson, robot);
                        if (watson->noModifyCharacterStats)
                            watson_bag->insert(robot->getItem());
                        else
                        {
                            if (robot->getName() == "RobotS")
                            ;
                            else if (robot->getName() == "RobotW")
                            {
                                if (watson->getHp() > 300)
                                    watson_bag->insert(robot->getItem());
                                else
                                    watson->setHp(watson->getHp() * 0.85);
                            }
                            else if (robot->getName() == "RobotSW")
                            {
                                if ((watson->getHp() > 165) && (watson->getExp() > 600))
                                    watson_bag->insert(robot->getItem());
                                else
                                {
                                    watson->setHp(sherlock->getHp() * 0.85);
                                    watson->setExp(sherlock->getExp() * 0.85);
                                }
                            }
                            else if (robot->getName() == "RobotC")
                                watson_bag->insert(robot->getItem());
                            BaseItem *item = watson_bag->get();
                            if (item)
                                if (item->canUse(watson, robot))
                                    item->use(watson, robot);
                            watson->roundHp();
                            watson->roundExp();
                        }
                        watson->noModifyCharacterStats = false;
                    }
                }
            }
            if (isStop())
            {
                printStep(i);
                printResult();
                return;
            }
            if (verbose)
                printStep(i);
        }
    }
    printResult();
}
