#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Jset.h"

using namespace std;

int main()
{
    const int system = 2;
    Jset J[system] = { Jset("jset1.txt"), Jset("jset2.txt") };
    J->set();
    J->print();
}
