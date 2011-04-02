#include "utils/utils.h"
#include "utils/testUtils.h"
#include "utils/path.h"

#include <itpp/itsignal.h>
using namespace itpp;

#include <iostream>
using namespace std;

int main() {
    const double start = 0;
    const double end = 2;
    const double sampleRate = 22050;
    const double frequency = 3.5;
    const double noise = 2.0;
    const double nfft = 1024;
    const string fileName = PATH + "test/matlab/signal.it";

    vec time = getTime(start, end-1/sampleRate, 1/sampleRate);
    vec silence = getSilence(time);
    vec silenceSpectrum = getSpectrum(silence, nfft);

    vec signal = getSignal(time, frequency, noise);
    vec signalSpectrum = getSpectrum(signal, nfft);

    it_file file(fileName);

    print("- saving time vector ...");
    file << Name("time") << time;

    print("- saving silence ...");
    file << Name("silence") << silence;
    file << Name("silenceSpectrum") << silenceSpectrum;

    print("- saving signal ...");
    file << Name("signal") << signal;
    file << Name("signalSpectrum") << signalSpectrum;

    print("- saving sample rate ...");
    file << Name("sampleRate") << sampleRate;

    print("- saving fft samples number ...");
    file << Name("nfft") << nfft;

    file.flush();
    file.close();
    cout << "data saved to file: " << fileName << endl;

    return 0;
}
