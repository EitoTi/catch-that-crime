#include "StudyInPinkProgram.h"

int StudyInPinkProgram::getDistance(Position pos1, Position pos2) const
{
    return (abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol()));
}

int StudyInPinkProgram::findCardinalNumber(int n) const
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

Robot* StudyInPinkProgram::createRobot(Position criminal_pre_pos) const
{
    Robot* robot = NULL;
    if (Robot::isFirstRobot())
    {
        // arr_mv_objs->getCount() means adding robot from index 3 in the arr_mv_objs
        robot = new RobotC(arr_mv_objs->getCount(), criminal_pre_pos, map, criminal);
        Robot::setFirstRobot(false);
    }
    else
    {
        int distance_to_sherlock = getDistance(criminal_pre_pos, sherlock->getCurrentPosition());
        int distance_to_watson = getDistance(criminal_pre_pos, watson->getCurrentPosition());
        if (distance_to_sherlock < distance_to_watson)
            robot = new RobotS(arr_mv_objs->getCount(), criminal_pre_pos, map, criminal, sherlock);
        else if (distance_to_sherlock > distance_to_watson)
            robot = new RobotW(arr_mv_objs->getCount(), criminal_pre_pos, map, criminal, watson);
        else if (distance_to_sherlock == distance_to_watson)
            robot = new RobotSW(arr_mv_objs->getCount(), criminal_pre_pos, map, criminal, sherlock, watson);
    }
    return robot;
}

BaseItem* StudyInPinkProgram::robotHasItem(Position criminal_pre_pos) const
{
    BaseItem* robotHasItem = NULL;
    int n = findCardinalNumber(criminal_pre_pos.getRow() * criminal_pre_pos.getCol()); // find cardinal number of p = i * j

    if ((n >= 0) && (n <= 1))
        robotHasItem = new MagicBook();
    else if ((n >= 2) && (n <= 3))
        robotHasItem = new EnergyDrink();
    else if ((n >= 4) && (n <= 5))
        robotHasItem = new FirstAid();
    else if ((n >= 6) && (n <= 7))
        robotHasItem = new ExcemptionCard();
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
        default:
            challenge = "Invalid challenge code!";
            break;
        }
        robotHasItem = new PassingCard(challenge);
    }
    return robotHasItem;
}

void StudyInPinkProgram::exchangeItemProcess() const
{
    BaseItem* sherlock_exchange_item = sherlock_bag->get(PASSING_CARD);
    BaseItem* watson_exchange_item = watson_bag->get(EXCEMPTION_CARD);

    while (sherlock_exchange_item && watson_exchange_item)
    {
        watson_bag->insert(sherlock_exchange_item);
        sherlock_exchange_item = sherlock_bag->get(PASSING_CARD);

        sherlock_bag->insert(watson_exchange_item);
        watson_exchange_item = watson_bag->get(EXCEMPTION_CARD);
    }
}

void StudyInPinkProgram::sherlockMeetRobot(const int robotIndex) const
{
    // Sherlock meets Robot
    if (sherlock->getCurrentPosition().isEqual(arr_mv_objs->getMovingObjectAtIndex(robotIndex)->getCurrentPosition()))
    {
        Robot* robot = (Robot*)arr_mv_objs->getMovingObjectAtIndex(robotIndex);
        BaseItem* item = sherlock_bag->get(EXCEMPTION_CARD);
        if (item != NULL && item->canUse(sherlock, NULL))
            sherlock->noModifyCharacterStats = true; // Now sherlock can pass the robot's challenge and doesn't have changes to his stats 

        int robotType = robot->getType(); // C = 0, S = 1, W = 2, SW = 3
        switch (robotType)
        {
        case S:
            if (sherlock->getExp() > 400)
                sherlock_bag->insert(robot->getItem());
            else
                if (!sherlock->noModifyCharacterStats) // Sherlock doesn't have Excemption Card to pass the challenge
                    sherlock->setExp(sherlock->getExp() * 0.9);
            break;
        case W:
            sherlock_bag->insert(robot->getItem());
            break;
        case SW:
            if ((sherlock->getHp() > 335) && (sherlock->getExp() > 300))
                sherlock_bag->insert(robot->getItem());
            else
                if (!sherlock->noModifyCharacterStats)
                {
                    sherlock->setHp(sherlock->getHp() * 0.85);
                    sherlock->setExp(sherlock->getExp() * 0.85);
                }
            break;
        case C:
            if (sherlock->getExp() > 500) // Sherlock catch the crime --> Program ends
            {
                sherlock->setPos(criminal->getCurrentPosition());
                if (isStop())
                {
                    //printStep(step);
                    //break;
                    printResult();
                    return;
                }
            }
            else
                sherlock_bag->insert(robot->getItem());
            break;
        default:
            cout << "Invalid Robot Type!\n";
            break;
        }

        // Find in sherlock bag to find items that can heal hp or increase exp after solving robot's challenge
        item = sherlock_bag->get();
        if (item != NULL && item->canUse(sherlock, NULL))
            item->use(sherlock, NULL);

        // Finish using Excemption Card -> set noModifyCharacterStats back to false
        // if noModifyCharacterStats is true, 
        // then sherlock can pass challenge and have no changes to his stats (exp, hp)
        sherlock->noModifyCharacterStats = false;
    }
}

void StudyInPinkProgram::watsonMeetRobot(const int robotIndex) const
{
    // Watson meets Robot
    if (watson->getCurrentPosition().isEqual(arr_mv_objs->getMovingObjectAtIndex(robotIndex)->getCurrentPosition()))
    {
        Robot* robot = (Robot*)arr_mv_objs->getMovingObjectAtIndex(robotIndex);
        BaseItem* item = watson_bag->get(PASSING_CARD);
        if (item != NULL && item->canUse(watson, NULL))
            item->use(watson, robot);

        if (watson->passChallenge) // Passing Card helps pass the robot's challenge 
            watson_bag->insert(robot->getItem());
        else
        {
            int robotType = robot->getType(); // C = 0, S = 1, W = 2, SW = 3
            switch (robotType)
            {
            case S:
                break;
            case W:
                if (watson->getHp() > 350)
                    watson_bag->insert(robot->getItem());
                else
                    watson->setHp(watson->getHp() * 0.95);
                break;
            case SW:
                if ((watson->getHp() > 165) && (watson->getExp() > 600))
                    watson_bag->insert(robot->getItem());
                else
                {
                    watson->setHp(sherlock->getHp() * 0.85);
                    watson->setExp(sherlock->getExp() * 0.85);
                }
                break;
            case C:
                watson_bag->insert(robot->getItem());
                break;
            default:
                cout << "Invalid Robot Type!\n";
                break;
            }

            // Find in watson bag to find items that can heal hp or increase exp after solving robot's challenge
            item = watson_bag->get();
            if (item != NULL && item->canUse(watson, NULL))
                item->use(watson, NULL);
        }
        watson->passChallenge = false;
    }
}

void StudyInPinkProgram::sherlockMeetWatson() const
{
    // Exchanging items when sherlock & watson meet
    // The exchanged items are used for solving the robot's challenge
    if (sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition()))
        exchangeItemProcess();
}

void StudyInPinkProgram::criminalStep() const
{
    Position criminal_pre_pos = criminal->getPreviousPosition();

    Robot* robot = createRobot(criminal_pre_pos); // Create Robot
    BaseItem* item = robotHasItem(criminal_pre_pos); // Item that robot contains

    arr_mv_objs->add(robot);
    robot->setItem(item);
    criminal->setCriminalNumSteps(0);
}

void StudyInPinkProgram::sherlockStep() const
{
    // Sherlock and Watson meet
    sherlockMeetWatson();

    // Check if Sherlock meets Robot
    for (int robotIndex = 3; robotIndex < arr_mv_objs->getCount(); robotIndex++) // Loop through all robots in arr_mv_objs starting from index 3
        sherlockMeetRobot(robotIndex);
}

void StudyInPinkProgram::watsonStep() const
{
    // Sherlock and Watson meet
    sherlockMeetWatson();

    // Check if Sherlock meets Robot
    for (int robotIndex = 3; robotIndex < arr_mv_objs->getCount(); robotIndex++) // Loop through all robots in arr_mv_objs starting from index 3
        watsonMeetRobot(robotIndex);
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
    return ((sherlock->getHp() == 0) || (watson->getHp() == 0) || sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()) || watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) ? true : false;
}

void StudyInPinkProgram::printResult() const
{
    if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        cout << "Sherlock caught the criminal" << endl;
    else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
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
    for (int step = 0; step <= config->num_steps; ++step)
    {
        for (int arrayIndex = 0; arrayIndex < arr_mv_objs->getCount(); ++arrayIndex)
        {
            MovingObject *obj = arr_mv_objs->getMovingObjectAtIndex(arrayIndex);
            obj->move(); // Also check for case of meeting Fake Wall here!

            // Create a robot every 3 steps of criminal
            if (obj->getName() == "Criminal" && criminal->getCriminalNumSteps() == 3)
                criminalStep();
            else if (obj->getName() == "Sherlock")
                sherlockStep();
            else if (obj->getName() == "Watson")
                watsonStep();
            else if ((arrayIndex >= 3 && arrayIndex < arr_mv_objs->getCount()) && (((Robot*)obj)->getType() == C || ((Robot*)obj)->getType() == S || ((Robot*)obj)->getType() == SW || ((Robot*)obj)->getType() == W))
            {
                sherlockMeetRobot(arrayIndex);
                watsonMeetRobot(arrayIndex);
            }

            if (isStop())
            {
                //printStep(step);
                //break;
                printResult();
                return;
            }
            if (verbose)
                printStep(step);
        }
    }
    printResult();
}
