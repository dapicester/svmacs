#ifndef FIXTURE_H_
#define FIXTURE_H_

#include "features/feature.h"
#include "testUtils.h"

// FIXME: this
#ifdef ENABLE_REGRESSION_TEST
#include "utils/path.h"
namespace {
const std::string MATLAB_FILE = PATH + "test/matlab/matlab.it";
const std::string SIGNAL_FILE = PATH + "test/matlab/signal.it";
}
#else
#include "utils/utils.h"
#endif

namespace test {

/// length of the input/output vector
const int FEATURES = 12;

struct TestData {
    itpp::vec samples;
    itpp::vec spectrum;
    itpp::vec expected;
};

struct Fixture {
    Fixture() {
#ifdef ENABLE_REGRESSION_TEST
        it_file file;

        file.open(SIGNAL_FILE);
        file >> Name("sampleRate") >> sampleRate;
        file >> Name("nfft") >> nfft;
        file >> Name("silence") >> silence.samples;
        file >> Name("silenceSpectrum") >> silence.spectrum;
        file >> Name("signal") >> signal.samples;
        file >> Name("signalSpectrum") >> signal.spectrum;
        file.close();

        file.open(MATLAB_FILE);
        file >> Name("featuresSignal") >> signal.expected;
        file >> Name("featuresSilence") >> silence.expected; // FIXME: wrong type?
        silence.expected = zeros(1,12);
        file >> Name("wts") >> filterBank;
        file.close();
#else
        sampleRate = 22050;
        nfft = 1024;

        const itpp::vec& time = getTime(0, 2 - 1/nfft, 1/nfft);
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
    //itpp::mat filterBank; /* MFCC only */
};

/// Extract feature
itpp::vec extract(const svmacs::Feature& feature, const TestData& input) {
    itpp::vec result = itpp::zeros(FEATURES);
    switch (feature.getType()) {
    case svmacs::TEMPORAL:
        feature.extract(input.samples, &result); 
        break;
    case svmacs::SPECTRAL:
        feature.extract(input.spectrum, &result); 
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
