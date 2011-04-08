#include "FeatureTester.h"
#include "features/feature.h"
#include "utils/testUtils.h"

#ifdef ENABLE_REGRESSION
    #include "utils/path.h"
    const std::string MATLAB_FILE = PATH + "test/matlab/matlab.it";
    const std::string SIGNAL_FILE = PATH + "test/matlab/signal.it";
#else
    #include "utils/utils.h"
#endif

CPPUNIT_TEST_SUITE_REGISTRATION(FeatureTest);

using namespace itpp;

const double FeatureTest::DELTA = 1e-9;

void FeatureTest::setUp() {
#ifdef ENABLE_REGRESSION
    it_file file;

    rDebug("loading signal file ...");
    file.open(SIGNAL_FILE);
    file >> Name("sampleRate") >> sampleRate;
    file >> Name("nfft") >> nfft;
    file >> Name("silence") >> silence.samples;
    file >> Name("silenceSpectrum") >> silence.spectrum;
    file >> Name("signal") >> signal.samples;
    file >> Name("signalSpectrum") >> signal.spectrum;
    file.close();

    rDebug("loading features file ...");
    file.open(MATLAB_FILE);
    file >> Name("featuresSignal") >> signal.expected;
    //file >> Name("featuresSilence") >> silence.expected; // FIXME: wrong type?
    silence.expected = zeros(1,12);
    file >> Name("wts") >> filterBank;
    file.close();
#else
    sampleRate = 22050;
    nfft = 1024;

    vec time = getTime(0, 2 - 1/nfft, 1/nfft);
    silence.samples = getSilence(time);
    silence.spectrum = getSpectrum(silence.samples, nfft);

    signal.samples = getSignal(time, 3.5, 2.0);
    signal.spectrum = getSpectrum(signal.samples, nfft);
#endif

    feature = setFeature();
}

void FeatureTest::tearDown() {
    delete feature;
}

static const int FEATURES = 12;

void FeatureTest::testSignal() {
    rDebug("extracting on signal ...");
    vec data = extract(signal);
#ifdef ENABLE_REGRESSION
    rDebug("regression test on signal ...");
    doRegressionTest(signal.expected, data);
#endif
}

void FeatureTest::testSilence() {
    rDebug("extracting on silence ...");
    vec data = extract(silence);
#ifdef ENABLE_REGRESSION
    rDebug("regression test on silence ...");
    doRegressionTest(silence.expected, data);
#endif
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
