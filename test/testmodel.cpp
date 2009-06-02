/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "range.h"
using namespace model;

#include <iostream>
using namespace std;

#define PRINT(X) cout << #X << "\n" << X << endl; 

void testScaleData() {
    mat input = 
    "0.2500    0.5000    0.7500    1.0000    1.2500    1.5000    1.7500    2.0000;"
    "2.2500    2.0000    1.7500    1.5000    1.2500    1.0000    0.7500    0.5000;"
    "0.5000    1.0000    1.5000    2.0000    2.5000    3.0000    3.5000    4.0000;"
    "4.5000    4.0000    3.5000    3.0000    2.5000    2.0000    1.5000    1.0000;"
    "1.0000    2.0000    3.0000    4.0000    5.0000    6.0000    7.0000    8.0000;"
    "9.0000    8.0000    7.0000    6.0000    5.0000    4.0000    3.0000    2.0000;"
    "2.0000    4.0000    6.0000    8.0000   10.0000   12.0000   14.0000   16.0000;"
   "18.0000   16.0000   14.0000   12.0000   10.0000    8.0000    6.0000    4.0000";
   
   mat range = 
   " 0     0     0     0     0     0     0     0;"
   "10    10    10    10    10    10    10    10";

   mat expected =
   "-0.9500   -0.9000   -0.8500   -0.8000   -0.7500   -0.7000   -0.6500   -0.6000;"
   "-0.5500   -0.6000   -0.6500   -0.7000   -0.7500   -0.8000   -0.8500   -0.9000;"
   "-0.9000   -0.8000   -0.7000   -0.6000   -0.5000   -0.4000   -0.3000   -0.2000;"
   "-0.1000   -0.2000   -0.3000   -0.4000   -0.5000   -0.6000   -0.7000   -0.8000;"
   "-0.8000   -0.6000   -0.4000   -0.2000         0    0.2000    0.4000    0.6000;"
   " 0.8000    0.6000    0.4000    0.2000         0   -0.2000   -0.4000   -0.6000;"
   "-0.6000   -0.2000    0.2000    0.6000    1.0000    1.4000    1.8000    2.2000;"
   " 2.6000    2.2000    1.8000    1.4000    1.0000    0.6000    0.2000   -0.2000";

   mat* scaled = scaleData(input,range);
   PRINT(expected);
   PRINT(*scaled);
    
//   if (expected != *scaled)
//      exit(1);
}

int main() {
    PRINT(range);
    
    testScaleData();   
}