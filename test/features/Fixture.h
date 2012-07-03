#ifndef FIXTURE_H_
#define FIXTURE_H_

#include "features/feature.hpp"
#include "testconfig.h"
#include "testUtils.h"
#include "utils/utils.h"

namespace test {

/// length of the input/output vector
const int FEATURES = 12;

/// Test data structure.
struct TestData {
    itpp::vec samples;  ///< input signal
    itpp::vec spectrum; ///< signal spectrum
    itpp::vec expected; ///< expected result
};

/// Feature test fixture.
struct Fixture {
    Fixture() {
#ifdef ENABLE_REGRESSION_TEST
        using namespace itpp;

        it_file file;

        file.open(TEST_DATA_DIR "/matlab/signal.it");
        file >> Name("sampleRate") >> sampleRate;
        file >> Name("nfft") >> nfft;
        file >> Name("silence") >> silence.samples;
        file >> Name("silenceSpectrum") >> silence.spectrum;
        file >> Name("signal") >> signal.samples;
        file >> Name("signalSpectrum") >> signal.spectrum;
        file.close();

        file.open(TEST_DATA_DIR "/matlab/matlab.it");
        file >> Name("featuresSignal") >> signal.expected;
        file >> Name("featuresSilence") >> silence.expected;
        silence.expected = zeros(1,12);
#ifdef MFCC_FILE
        file >> Name("wts") >> filterBank;
#endif
        file.close();
#else
        sampleRate = 22050;
        nfft = 1024;

        const itpp::vec& time = getTime(0.0, 2 - 1/nfft, 1/nfft);
        silence.samples = getSilence(time.size());
        silence.spectrum = svmacs::getSpectrum(silence.samples, nfft);
        signal.samples = getSignal(time, 3.5, 2.0);
        signal.spectrum = svmacs::getSpectrum(signal.samples, nfft);
#endif
    }

    double sampleRate;
    double nfft;
    TestData signal;
    TestData silence;
#ifdef MFCC_FILE
    itpp::mat filterBank;
#endif
};

/// Extract feature
itpp::vec extract(const svmacs::Feature& feature, const TestData& input) {
    itpp::vec result = itpp::zeros(FEATURES);
    switch (feature.getType()) {
    case svmacs::Feature::TEMPORAL:
        feature.extract(input.samples, result);
        break;
    case svmacs::Feature::SPECTRAL:
        feature.extract(input.spectrum, result);
        break;
    }
    //print("result", result);

    return result;
}

#ifdef ENABLE_REGRESSION_TEST
/// double comparison tolerance
const double DELTA = 1e-9;

void doRegressionTest(const itpp::vec& expected, const itpp::vec& actual);
#endif

void doTest(const svmacs::Feature& feature, const TestData& input) {
    const itpp::vec& output = extract(feature, input);
#ifdef ENABLE_REGRESSION_TEST
    doRegressionTest(input.expected, output);
#endif
}

} /* namespace test */

#endif // FIXTURE_H_
