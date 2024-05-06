#pragma once
#ifndef _CONFIGURATION
#include "position.h"
class Configuration
{
private:
	int map_num_rows = 0, map_num_cols = 0;
	int max_num_moving_objects = 0;
	int num_walls = 0;
	Position* arr_walls = nullptr;
	int num_fake_walls = 0;
	Position* arr_fake_walls = nullptr;
	string sherlock_moving_rule;
	Position sherlock_init_pos;
	int sherlock_init_hp = 0;
	int sherlock_init_exp = 0;
	string watson_moving_rule;
	Position watson_init_pos;
	int watson_init_hp = 0;
	int watson_init_exp = 0;
	Position criminal_init_pos;
	int num_steps = 0;
public:
	Configuration(const string&);
	~Configuration();
	string str() const;
};
#endif // !_CONFIGURATION
