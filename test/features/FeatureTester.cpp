#include "FeatureTester.h"
#include <utils/testUtils.h>

CPPUNIT_TEST_SUITE_REGISTRATION( FeatureTest );

FeatureTest::FeatureTest() {
  feature = setFeature();
}

FeatureTest::~FeatureTest() {
  delete feature;
}

void 
FeatureTest::setUp(){
  silence = getSilence();
  signal = getSignal();
}

void 
FeatureTest::tearDown() {
}

void 
FeatureTest::testSignal() {
  itpp::vec result;
  feature->extract(signal, result);
  print("result", result);
}

void 
FeatureTest::testSilence() {
  itpp::vec result;
  feature->extract(silence, result);
  print("result", result);
}
