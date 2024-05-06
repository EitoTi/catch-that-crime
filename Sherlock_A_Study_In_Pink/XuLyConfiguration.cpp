#include "configuration.h"

Configuration::Configuration(const string& filepath)
{
	ifstream fileInput(filepath);

	if (fileInput.fail())
		cout << "Failed to open this file!" << endl;

	// Read each line of file
	string property;
	char tmp;
	int tmpInt = 0;
	while (!fileInput.eof())
	{
		char temp[255];
		fileInput.getline(temp, 255);
		string line = temp;

		for (int i = 0; i < line.size(); ++i)
			if (line[i] == '=')
				line[i] = ' ';

		stringstream sso(line);
		sso >> property;

		if (property == "MAP_NUM_ROWS")
			sso >> map_num_rows;
		else if (property == "MAP_NUM_COLS")
			sso >> map_num_cols;
		else if (property == "MAX_NUM_MOVING_OBJECTS")
			sso >> max_num_moving_objects;
		else if (property == "NUM_WALLS")
			sso >> num_walls;
		else if (property == "ARRAY_WALLS" || property == "ARRAY_FAKE_WALLS")
		{
			string array;
			sso >> array;

			// [(1,2);(2,3);(3,4)] --> remove '[' and ']'
			array = array.substr(1, array.size() - 2);

			stringstream ss(array);
			string toaDo;
			int size = (property == "ARRAY_WALLS") ? num_walls : num_fake_walls;
			Position* positions = new Position[size];

			// Tach string theo ';'
			int i = 0;
			while (getline(ss, toaDo, ';'))
			{
				// toaDo = (1,2)
				Position pos(toaDo);
				if (i < size)
					positions[i++] = pos;
			}

			if (property == "ARRAY_WALLS")
				arr_walls = positions;
			else
				arr_fake_walls = positions;
		}
		else if (property == "NUM_FAKE_WALLS")
			sso >> num_fake_walls;
		else if (property == "SHERLOCK_MOVING_RULE")
			sso >> sherlock_moving_rule;
		else if (property == "SHERLOCK_INIT_POS")
		{
			int r, c;
			sso >> tmp >> r >> tmp >> c >> tmp;
			sherlock_init_pos.setRow(r);
			sherlock_init_pos.setCol(c);
		}
		else if (property == "SHERLOCK_INIT_HP")
			sso >> sherlock_init_hp;
		else if (property == "SHERLOCK_INIT_EXP")
			sso >> sherlock_init_exp;
		else if (property == "WATSON_MOVING_RULE")
			sso >> watson_moving_rule;
		else if (property == "WATSON_INIT_POS")
		{
			int r, c;
			sso >> tmp >> r >> tmp >> c >> tmp;
			watson_init_pos.setRow(r);
			watson_init_pos.setCol(c);
		}
		else if (property == "WATSON_INIT_HP")
			sso >> watson_init_hp;
		else if (property == "WATSON_INIT_EXP")
			sso >> watson_init_exp;
		else if (property == "CRIMINAL_INIT_POS")
		{
			int r, c;
			sso >> tmp >> r >> tmp >> c >> tmp;
			criminal_init_pos.setRow(r);
			criminal_init_pos.setCol(c);
		}
		else if (property == "NUM_STEPS")
			sso >> num_steps;
	}
	cout << endl;

	fileInput.close();
}
Configuration::~Configuration()
{
	delete[] arr_walls;
	delete[] arr_fake_walls;
}
string Configuration::str() const
{
	string result = "Configuration[\n";
	result += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
	result += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
	result += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
	result += "NUM_WALLS=" + to_string(num_walls) + "\n";
	result += "ARRAY_WALLS=[";
	for (int i = 0; i < num_walls; ++i)
	{
		result += arr_walls[i].str();
		if (i < num_walls - 1)
			result += ";";
	}
	result += "]\n";
	result += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
	result += "ARRAY_FAKE_WALLS=[";
	for (int i = 0; i < num_fake_walls; ++i)
	{
		result += arr_fake_walls[i].str();
		if (i < num_fake_walls - 1)
			result += ";";
	}
	result += "]\n";
	result += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n";
	result += "SHERLOCK_INIT_POS=" + sherlock_init_pos.str() + "\n";
	result += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n";
	result += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
	result += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n";
	result += "WATSON_INIT_POS=" + watson_init_pos.str() + "\n";
	result += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n";
	result += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
	result += "CRIMINAL_INIT_POS=" + criminal_init_pos.str() + "\n";
	result += "NUM_STEPS=" + to_string(num_steps) + "\n";
	result += "]";
	return result;
}
