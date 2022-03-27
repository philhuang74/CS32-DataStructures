//
//  testCarMap.cpp
//  CS32_HW1
//
//  Created by Philip Huang on 1/16/22.
//

#include "CarMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    CarMap c;
    c.addCar("McQueen");
    c.addCar("Mercedes");
    c.drive("McQueen", 10001);
    assert(c.fleetSize()==2);
    assert(c.miles("McQueen") == 10001);
    c.print();
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
