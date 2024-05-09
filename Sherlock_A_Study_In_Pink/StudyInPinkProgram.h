#pragma once
#ifndef _STUDY_IN_PINK
#include "position.h"
#include "movingObject.h"
#include "configuration.h"
#include "map.h"
#include "arrayMovingObject.h"
#include "BaseBag.h"
#include "baseItem.h"

int getDistance(Position pos1, Position pos2);
int findMainNum(int n);

class StudyInPinkProgram
{
    friend class TestStudyInPink;
private:
    Configuration *config;
    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;
    Map *map;
    ArrayMovingObject *arr_mv_objs;
    SherlockBag *sherlock_bag;
    WatsonBag *watson_bag;
public:
    StudyInPinkProgram(const string&);
    ~StudyInPinkProgram();
    bool isStop() const;
    void printResult() const;
    void printStep(int) const;
    void run(bool);
};
#endif // !_STUDY_IN_PINK