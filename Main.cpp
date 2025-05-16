#include <iostream>
#include "BattleField.h"
#include <vector>
#include <string>
#include "Unit.h"
#include "tests.h"
using namespace std;

int main()
{
    cout << "Battlefield test " << (test_battlefield() ? "passed" : "failed") << endl;
    cout << "fire test " << (test_fire() ? "passed" : "failed") << endl;
    cout << "respawn test" << (test_respawn() ? "passed":"failed")<< endl;
    return 0;
}
