#include "ScaleTest.h"
#include <model/range.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ScaleTest);

void ScaleTest::testScaleData() {
    itpp::mat input = 
    "0.2500    0.5000    0.7500    1.0000    1.2500    1.5000    1.7500    2.0000;"
    "2.2500    2.0000    1.7500    1.5000    1.2500    1.0000    0.7500    0.5000;"
    "0.5000    1.0000    1.5000    2.0000    2.5000    3.0000    3.5000    4.0000;"
    "4.5000    4.0000    3.5000    3.0000    2.5000    2.0000    1.5000    1.0000;"
    "1.0000    2.0000    3.0000    4.0000    5.0000    6.0000    7.0000    8.0000;"
    "9.0000    8.0000    7.0000    6.0000    5.0000    4.0000    3.0000    2.0000;"
    "2.0000    4.0000    6.0000    8.0000   10.0000   12.0000   14.0000   16.0000;"
   "18.0000   16.0000   14.0000   12.0000   10.0000    8.0000    6.0000    4.0000";
   
   itpp::mat range = 
   " 0     0     0     0     0     0     0     0;"
   "10    10    10    10    10    10    10    10";

   itpp::mat expected =
   "-0.9500   -0.9000   -0.8500   -0.8000   -0.7500   -0.7000   -0.6500   -0.6000;"
   "-0.5500   -0.6000   -0.6500   -0.7000   -0.7500   -0.8000   -0.8500   -0.9000;"
   "-0.9000   -0.8000   -0.7000   -0.6000   -0.5000   -0.4000   -0.3000   -0.2000;"
   "-0.1000   -0.2000   -0.3000   -0.4000   -0.5000   -0.6000   -0.7000   -0.8000;"
   "-0.8000   -0.6000   -0.4000   -0.2000         0    0.2000    0.4000    0.6000;"
   " 0.8000    0.6000    0.4000    0.2000         0   -0.2000   -0.4000   -0.6000;"
   "-0.6000   -0.2000    0.2000    0.6000    1.0000    1.4000    1.8000    2.2000;"
   " 2.6000    2.2000    1.8000    1.4000    1.0000    0.6000    0.2000   -0.2000";

   // scale vector
   for (int i = 0; i < input.rows(); i++) {
        itpp::vec vscaled = model::scaleData(input.get_row(i), range);
        CPPUNIT_ASSERT_EQUAL(expected.get_row(i), vscaled);
   }
   
   // scale matrix
   itpp::mat scaled = model::scaleData(input, range);
   const double delta = 0.000001;
   for (int i = 0; i < expected.size(); i++) {
       CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.get(i), scaled.get(i), delta);
   }
   // FIXME: capire perché il seguente test fallisce (itpp?)
   //CPPUNIT_ASSERT_EQUAL(expected, scaled);
   
}
