/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "svmclassifier.h"
#include "range.h"
using namespace model;

#include "svm.h"

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

   mat scaled = scaleData(input,range);
   PRINT(expected);
   PRINT(scaled);
    
//  if (expected != scaled)
//     exit(1);

    vec vscaled = scaleData(input.get_row(0), range);
    PRINT(vscaled);

//   if (expected.get_row(0) != vscaled)
//      exit(1);

}

void testNode() {
    vec uno = "1 0 1 0";
    PRINT(uno);

    PRINT(sizeof(svm_node));
    PRINT(sizeof(svm_node*));

    svm_node array[4];
    for (int i=0; i<uno.length(); +i++) {
	array[i].index = i;
	array[i].value = uno[i];
    }
    
    
    for (int i=0; i<uno.length(); +i++) {
	int index = array[i].index;
	double val = array[i].value;
	cout << index << ":" << val << " ";
	if (i==uno.length()-1) cout << endl; 
    }

    svm_node* ptr = array;
    for(int i = 0; i<uno.length(); i++) {
	cout << ptr->index << ":" << ptr->value << " ";
	ptr++;
	//if (i==uno.length()-1) cout << endl; 
    }
    
}

int main() {
    //PRINT(getRange());
    
    //testScaleData();

    testNode();
}
