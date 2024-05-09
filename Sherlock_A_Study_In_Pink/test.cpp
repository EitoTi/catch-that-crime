#include "StudyInPinkProgram.h"

using namespace std;

int main()
{
  StudyInPinkProgram *test = new StudyInPinkProgram("sa_tc_02_config.txt");
  test->run(true);
  delete test;
  return 0;
}
