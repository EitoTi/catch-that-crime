#pragma once
#ifndef _STUDY_IN_PINK
#include "position.h"
#include "movingObject.h"
#include "configuration.h"
#include "map.h"
#include "arrayMovingObject.h"
#include "BaseBag.h"
#include "baseItem.h"


class StudyInPinkProgram
{
private:
    Configuration* config;
    Sherlock* sherlock;
    Watson* watson;
    Criminal* criminal;
    Map* map;
    ArrayMovingObject *arr_mv_objs;
    SherlockBag *sherlock_bag;
    WatsonBag *watson_bag;

    int getDistance(Position, Position) const;

    int findCardinalNumber(int) const;

    // Process of creating robot basing on moving process of criminal
    Robot* createRobot(Position);

    BaseItem* robotHasItem(Position);

    // Sherlock exchanges frist, then watson performs that
    void exchangeItemProcess() const;
public:
    StudyInPinkProgram(const string&);
    ~StudyInPinkProgram();
    bool isStop() const;
    void printResult() const;
    void printStep(int) const;
    void run(bool);
    friend class TestStudyInPink;
};
#endif // !_STUDY_IN_PINK