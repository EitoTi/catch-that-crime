#include "configuration.h"

Configuration::Configuration(const string& filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
        cout << "Failed to open file!" << endl;
    string str;
    while (getline(file, str))
    {
        for (char& c : str)
            if (c == '=')
                c = ' ';
        stringstream ss(str);
        string property;
        ss >> property;
        if (property == "MAP_NUM_ROWS")
            ss >> map_num_rows;
        else if (property == "MAP_NUM_COLS")
            ss >> map_num_cols;
        else if (property == "MAX_NUM_MOVING_OBJECTS")
            ss >> max_num_moving_objects;
        else if (property == "ARRAY_WALLS")
        {
            string temp;
            ss >> temp;
            temp = temp.substr(1, temp.size() - 2);
            for (char& c : temp)
                if (c == ';')
                    c = ' ';
            stringstream arr(temp);
            char discard;
            int r, c;
            int count = 0;
            while (arr >> discard >> r >> discard >> c >> discard)
                count++;
            arr_walls = new Position[count];
            arr.clear();
            arr.seekg(0);
            num_walls = count;
            for (int i = 0; i < count; i++)
            {
                arr >> discard >> r >> discard >> c >> discard;
                arr_walls[i] = Position(r, c);
            }
        }
        else if (property == "ARRAY_FAKE_WALLS")
        {
            string temp;
            ss >> temp;
            temp = temp.substr(1, temp.size() - 2);
            for (char& c : temp)
                if (c == ';')
                    c = ' ';
            stringstream arr(temp);
            char discard;
            int r, c;
            int count = 0;
            while (arr >> discard >> r >> discard >> c >> discard)
                count++;
            arr_fake_walls = new Position[count];
            arr.clear();
            arr.seekg(0);
            num_fake_walls = count;
            for (int i = 0; i < count; i++)
            {
                arr >> discard >> r >> discard >> c >> discard;
                arr_fake_walls[i] = Position(r, c);
            }
        }
        else if (property == "SHERLOCK_MOVING_RULE")
            ss >> sherlock_moving_rule;
        else if (property == "SHERLOCK_INIT_POS")
        {
            int r, c;
            char temp;
            ss >> temp >> r >> temp >> c >> temp;
            sherlock_init_pos = Position(r, c);
        }
        else if (property == "SHERLOCK_INIT_HP")
            ss >> sherlock_init_hp;
        else if (property == "SHERLOCK_INIT_EXP")
            ss >> sherlock_init_exp;
        else if (property == "WATSON_MOVING_RULE")
            ss >> watson_moving_rule;
        else if (property == "WATSON_INIT_POS")
        {
            int r, c;
            char temp;
            ss >> temp >> r >> temp >> c >> temp;
            watson_init_pos = Position(r, c);
        }
        else if (property == "WATSON_INIT_HP")
            ss >> watson_init_hp;
        else if (property == "WATSON_INIT_EXP")
            ss >> watson_init_exp;
        else if (property == "CRIMINAL_INIT_POS")
        {
            int r, c;
            char temp;
            ss >> temp >> r >> temp >> c >> temp;
            criminal_init_pos = Position(r, c);
        }
        else if (property == "NUM_STEPS")
            ss >> num_steps;
    }
    file.close();
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
