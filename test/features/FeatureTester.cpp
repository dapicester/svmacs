#include "FeatureTester.h"
#include "features/feature.h"
#include "utils/testUtils.h"
#include "utils/path.h"

using namespace itpp;

CPPUNIT_TEST_SUITE_REGISTRATION(FeatureTest);

const std::string MATLAB_FILE = PATH + "test/matlab/matlab.it";
const std::string SIGNAL_FILE = PATH + "test/matlab/signal.it";

void FeatureTest::setUp() {
    feature = setFeature();

    it_file file;

    file.open(SIGNAL_FILE);
    file >> Name("sampleRate") >> sampleRate;
    file >> Name("nfft") >> nfft;
    file >> Name("silence") >> silence.samples;
    file >> Name("silenceSpectrum") >> silence.spectrum;
    file >> Name("signal") >> signal.samples;
    file >> Name("signalSpectrum") >> signal.samples;
    file.close();

    file.open(MATLAB_FILE);
    file >> Name("featuresSignal") >> signal.expected;
    file >> Name("featuresSilence") >> silence.expected;
    file.close();
}

void FeatureTest::tearDown() {
    delete feature;
}

static const int FEATURES = 12;

void FeatureTest::testSignal() {
    vec data = extract(signal);
    doRegressionTest(signal.expected, data);
}

void FeatureTest::testSilence() {
    vec data = extract(silence);
    doRegressionTest(silence.expected, data);
}

vec FeatureTest::extract(const testData& input) const {
    vec result = zeros(FEATURES);

    switch (feature->getType()) {
    case TEMPORAL:
        feature->extract(input.samples, result); break;
    case SPECTRAL:
        feature->extract(input.spectrum, result); break;
    }
    print("result", result);

    return result;
}
