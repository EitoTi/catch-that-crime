#include "StudyInPinkProgram.h"
#include <cstdlib>
#include <filesystem>

using namespace std;

#ifdef _WIN32
const std::string path_separator = "\\";
#else
const std::string path_separator = "/";
#endif

#ifdef _WIN32
const std::string open_cmd = "start";
#elif __APPLE__
const std::string open_cmd = "open";
#else
const std::string open_cmd = "xdg-open";
#endif


bool compareFiles(const string& p1, const string& p2)
{
    ifstream f1(p1, ifstream::binary | ifstream::ate);
    ifstream f2(p2, ifstream::binary | ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        return false; // file problem
    }

    if (f1.tellg() != f2.tellg())
    {
        return false; // size mismatch
    }

    // seek back to beginning and use equal to compare contents
    f1.seekg(0, ifstream::beg);
    f2.seekg(0, ifstream::beg);
    return equal(istreambuf_iterator<char>(f1.rdbuf()),
        istreambuf_iterator<char>(),
        istreambuf_iterator<char>(f2.rdbuf()));
}


void printFile(const string& p1)
{
    ifstream f1(p1);
    string line;
    while (getline(f1, line))
    {
        std::cout << line << endl;
    }
}


void clearScreen()
{
#ifdef _WIN32
    string clear_command = "cls";
#else
    string clear_command = "printf '\\33c\\e[3J'";
#endif
    system(clear_command.c_str());
}


BaseItem* stringtoItem(string input)
{
    if (input == "MAGIC_BOOK")
        return new MagicBook();
    else if (input == "ENERGY_DRINK")
        return new EnergyDrink();
    else if (input == "FIRST_AID")
        return new FirstAid;
    else if (input == "EXCEMPTION_CARD")
        return new ExcemptionCard();
    else
        return new PassingCard("all");
}


ItemType stringtoItemType(string input)
{
    if (input == "MAGIC_BOOK")
        return MAGIC_BOOK;
    else if (input == "ENERGY_DRINK")
        return ENERGY_DRINK;
    else if (input == "FIRST_AID")
        return FIRST_AID;
    else if (input == "EXCEMPTION_CARD")
        return EXCEMPTION_CARD;
    else
        return PASSING_CARD;
}

class TestStudyInPink
{
public:
    static void check_01(string input_file, string output_file)
    {
        ifstream infile(input_file);

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules;
        Position init_pos;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules;

        Position* arr_walls = new Position[num_walls];
        Position* arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                init_pos = Position(temp_pos);
                break;
            }
        }

        Map* map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Sherlock* sherlock = new Sherlock(1, moving_rules, init_pos, map, 100, 100);
        infile.close();

        ArrayMovingObject* arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(sherlock);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;

        for (int i = 0; i < num_steps; i++)
        {
            outfile << "STEP" << i + 1 << ": * Sherlock makes a move" << endl;
            sherlock->move();
            outfile << arr_moving_obj->str() << endl;
        }
        outfile << "End." << endl;
        outfile.close();
    }
    static void check_02(string input_file, string output_file)
    {
        ifstream infile(input_file); 

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules;
        Position init_pos;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules;

        Position* arr_walls = new Position[num_walls];
        Position* arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                init_pos = Position(temp_pos);
                break;
            }
        }

        Map* map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson* watson = new Watson(0, moving_rules, init_pos, map, 100, 100);
        infile.close();

        ArrayMovingObject* arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(watson);

        ofstream outfile(output_file);
        outfile << watson->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            outfile << "STEP" << i + 1 << ": * Watson makes a move" << endl;
            watson->move();
            outfile << arr_moving_obj->str() << endl;
        }
        outfile << "End." << endl;
        outfile.close();
    }
    static void check_03(string input_file, string output_file)
    {
        ifstream infile(input_file);

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position* arr_walls = new Position[num_walls];
        Position* arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map* map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson* watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock* sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal* criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();

        ArrayMovingObject* arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(criminal);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            outfile << "STEP" << i + 1 << ": * Sherlock, Watson, Criminal makes a move" << endl;
            sherlock->move();
            watson->move();
            criminal->move();
            outfile << arr_moving_obj->str() << endl;
        }
        outfile << "End." << endl;
        outfile.close();
    }
    static void check_04(string input_file, string output_file)
    {
        Configuration* config = new Configuration(input_file);
        ofstream outfile(output_file);
        outfile << config->str() << endl;
        outfile << "End." << endl;
        outfile.close();
       
    }
    static void check_05(string input_file, string output_file)
    {
        ifstream infile(input_file);

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position* arr_walls = new Position[num_walls];
        Position* arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map* map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson* watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock* sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal* criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotC* robotC = nullptr;

        ArrayMovingObject* arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(criminal);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotC != nullptr)
                robotC->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 3)
            {
                outfile << "* Create new RobotC" << endl;
                robotC = new RobotC(3, temp_pos, map, criminal);
                outfile << robotC->str() << endl;
                arr_moving_obj->add(robotC);
            }
        }
        outfile << "End." << endl;
        outfile.close();

    }
    static void check_06(string input_file, string output_file)
    {
        ifstream infile(input_file);

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position* arr_walls = new Position[num_walls];
        Position* arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map* map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson* watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock* sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal* criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotS* robotS = nullptr;

        ArrayMovingObject* arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(criminal);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotS != nullptr)
                robotS->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 6)
            {
                outfile << "* Create new RobotS" << endl;
                robotS = new RobotS(4, temp_pos, map, criminal, sherlock);
                outfile << robotS->str() << endl;
                arr_moving_obj->add(robotS);
            }
        }
        outfile << "End." << endl;
        outfile.close();

    }
    static void check_07(string input_file, string output_file)
    {
        ifstream infile(input_file);

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position* arr_walls = new Position[num_walls];
        Position* arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map* map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson* watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock* sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal* criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotW* robotW = nullptr;

        ArrayMovingObject* arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(criminal);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotW != nullptr)
                robotW->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 9)
            {
                outfile << "* Create new RobotW" << endl;
                robotW = new RobotW(5, temp_pos, map, criminal, watson);
                outfile << robotW->str() << endl;
                arr_moving_obj->add(robotW);
            }
        }
        outfile << "End." << endl;
        outfile.close();



    }
    static void check_08(string input_file, string output_file)
    {
        ifstream infile(input_file);

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position* arr_walls = new Position[num_walls];
        Position* arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map* map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson* watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock* sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal* criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotSW* robotSW = nullptr;

        ArrayMovingObject* arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(criminal);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotSW != nullptr)
                robotSW->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 12)
            {
                outfile << "* Create new RobotWS" << endl;
                robotSW = new RobotSW(6, temp_pos, map, criminal, sherlock, watson);
                cout << robotSW->str() << "\n\nhi\n\n";
                outfile << robotSW->str() << endl;
                arr_moving_obj->add(robotSW);
            }
        }
        outfile << "End." << endl;
        outfile.close();


    }
    static void check_09(string input_file, string output_file)
    {
        int num_walls = 3;
        Position arr_walls[] = { Position(1, 2), Position(2, 3), Position(3, 4) };
        int num_fake_walls = 1;
        Position arr_fake_walls[] = { Position(2, 0) };
        Map* map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        ifstream infile(input_file);
        ofstream outfile(output_file);

        int hp_sher;
        int hp_wat;
        int exp_sher;
        int exp_wat;
        vector<BaseItem*> items;

        infile >> hp_sher;
        infile >> hp_wat;
        infile >> exp_sher;
        infile >> exp_wat;

        Sherlock* sherlock = new Sherlock(0, "RL", Position(1, 3), map, hp_sher, exp_sher);
        outfile << sherlock->str() << " HP: " << hp_sher << " EXP: " << exp_sher << endl;
        Watson* watson = new Watson(1, "UD", Position(2, 1), map, hp_wat, exp_wat);
        outfile << watson->str() << " HP: " << hp_wat << " EXP: " << exp_wat << endl;

        BaseBag* sher_bag = new SherlockBag(sherlock);
        outfile << sher_bag->str() << endl;
        BaseBag* wat_bag = new WatsonBag(watson);
        outfile << wat_bag->str() << endl;
        int numline = 3;
        string line;

        while (getline(infile, line))
        {
            numline++;
            istringstream iss(line);
            string command;
            iss >> command;

            if (command == "INSERT")
            {
                string input;
                iss >> input;
                outfile << "LINE " << numline << ": * Insert " << input << " into bag" << endl;
                BaseItem* tempitem = stringtoItem(input);
                items.push_back(tempitem);
                sher_bag->insert(tempitem);
                wat_bag->insert(tempitem);
                outfile << "SherlockBag: " << sher_bag->str() << endl;
                outfile << "WatsonBag " << wat_bag->str() << endl;
            }
            else if (command == "GET")
            {
                string input;
                iss >> input;
                outfile << "LINE " << numline << ": * Get " << input << " from bag" << endl;
                // Debug Base Bag
                /*outfile << endl << "Sherlock hp: " << sherlock->getHp() << endl;
                outfile << "Watson hp: " << watson->getHp() << endl;
                outfile << "Sherlock exp: " << sherlock->getExp() << endl;
                outfile << "Watson exp: " << watson->getExp() << endl;*/
                if (input.empty())
                {
                    sher_bag->get();
                    wat_bag->get();
                }
                else
                {
                    sher_bag->get(stringtoItemType(input));
                    wat_bag->get(stringtoItemType(input));
                }
                outfile << "SherlockBag: " << sher_bag->str() << endl;
                outfile << "WatsonBag " << wat_bag->str() << endl;
            }
        }
        infile.close();
        outfile << "End." << endl;
        outfile.close();

    }
    static void check_10(string input_file, string output_file)
    {
        StudyInPinkProgram* program = new StudyInPinkProgram(input_file);
        
        streambuf* oldcoutStreamBuf = std::cout.rdbuf();

        ofstream ofs(output_file);
        std::cout.rdbuf(ofs.rdbuf());
        
        program->run(true);
        std::cout << "End." << endl;
        
        std::cout.rdbuf(oldcoutStreamBuf);
    }
};

void printResult(string input_folder)
{

    std::cout << "Enter start input (0 - 499): ";
    int start_input = 0;
    // std::cin >> start_input;
    std::cout << "Enter end input (0 - 499): ";
    int end_input = 499;
    // std::cin >> end_input;

    std::string command = "mkdir -p testcase" + path_separator + input_folder + path_separator + "output";
    system(command.c_str());
    for (int i = start_input; i <= end_input; ++i)
    {
        clearScreen();
        std::cout << "Checking " << input_folder << " - Testcase: " << i << endl;
        string input_file = "testcase/" + input_folder + "/input/input" + to_string(i) + ".txt";
        string output_file = "testcase/" + input_folder + "/output/output" + to_string(i) + ".txt";
        string expect_file = "testcase/" + input_folder + "/expect/output" + to_string(i) + ".txt";

        if (input_folder == "Sherlock_move")
        {
            TestStudyInPink::check_01(input_file, output_file);
        }
        else if (input_folder == "Watson_move")
        {
            TestStudyInPink::check_02(input_file, output_file);
        }
        else if (input_folder == "Criminal_move")
        {
            TestStudyInPink::check_03(input_file, output_file);
        }
        else if (input_folder == "Configuration")
        {
            TestStudyInPink::check_04(input_file, output_file);
        }
        else if (input_folder == "RobotC_move")
        {
            TestStudyInPink::check_05(input_file, output_file);
        }
        else if (input_folder == "RobotS_move")
        {
            TestStudyInPink::check_06(input_file, output_file);
        }
        else if (input_folder == "RobotW_move")
        {
            TestStudyInPink::check_07(input_file, output_file);
        }
        else if (input_folder == "RobotSW_move")
        {
            TestStudyInPink::check_08(input_file, output_file);
        }
        else if (input_folder == "BaseBag")
        {
            TestStudyInPink::check_09(input_file, output_file);
        }
        else if (input_folder == "StudyPinkProgram")
        {
            TestStudyInPink::check_10(input_file, output_file);
        }

        if (!compareFiles(output_file, expect_file))
        {
            clearScreen();
            std::cout << "Test case " << i << " failed" << endl;
            std::cout << "Input file: " << input_file << endl;
            std::cout << "-------------------------------" << endl;
            std::cout << "Your output: " << output_file << endl;
            std::cout << "-------------------------------" << endl;
            std::cout << "Expected output: " << expect_file << endl;
            std::cout << "-------------------------------" << endl;
            std::cout << "Structure of input file: " << endl;
            printFile("testcase/" + input_folder + "/readme.txt");
            break;
        }
        if (i == 499)
        {
            clearScreen();
            std::cout << "All test cases passed" << endl;
            std::string command = "rmdir /S /Q testcase" + path_separator + input_folder + path_separator + "output";
            system(command.c_str());
        }
    }
}

int main()
{
    while (true)
    {
        clearScreen();
        int choice;
        std::cout << " 1. Check Sherlock's movement" << endl;
        std::cout << " 2. Check Waison's movement" << endl;
        std::cout << " 3. Check Sherlock, Watson, Criminal's movement. Not create robot" << endl;
        std::cout << " 4. Check Configuration" << endl;
        std::cout << " 5. Check RobotC's movement" << endl;
        std::cout << " 6. Check RobotS's movement" << endl;
        std::cout << " 7. Check RobotW's movement" << endl;
        std::cout << " 8. Check RobotSW's movement" << endl;
        std::cout << " 9. Check BaseBag" << endl;
        std::cout << "10. Check StudyPinkProgram" << endl;
        std::cout << "========================================" << endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearScreen();

        switch (choice)
        {
        case 1:
        {
            printResult("Sherlock_move");
            break;
        }
        case 2:
        {
            printResult("Watson_move");
            break;
        }
        case 3:
        {
            printResult("Criminal_move");
            break;
        }
        case 4:
        {
            printResult("Configuration");
            break;
        }
        case 5:
        {
            printResult("RobotC_move");
            break;
        }
        case 6:
        {
            printResult("RobotS_move");
            break;
        }
        case 7:
        {
            printResult("RobotW_move");
            break;
        }
        case 8:
        {
            printResult("RobotSW_move");
            break;
        }
        case 9:
        {
            printResult("BaseBag");
            break;
        }
        case 10:
        {
            printResult("StudyPinkProgram");
            break;
        }
        }
        std::cout << "========================================" << endl;
        std::cout << "Press 0 to exit, 1 to continue: ";
        std::cin >> choice;
        if (choice == 0)
        {
            break;
        }
    }
    return 0;
}