#include "utils/testUtils.h"

#include <itpp/itsignal.h>
using namespace itpp;

#include <iostream>
using namespace std;

//const static string PATH = "/home/paolo/NetBeansProjects/svmacs/test/matlab/";

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <output file path>" << endl;
        exit(1);
    }

    const string path(argv[1]);

    const double start = 0;
    const double end = 2;
    const double sampleRate = 22050;
    const double frequency = 3.5;
    const double noise = 2.0;
    const double nfft = 1024;
    const string fileName = path + "/test.it";

    vec time = getTime(start, end, 1/sampleRate);
    vec signal = getSignal(time, frequency, noise);
    vec spectrum = itpp::abs( itpp::fft( itpp::to_cvec(signal), nfft ) ).left(nfft/2);

    it_file file(fileName);
    file << Name("time") << time;
    file << Name("signal") << signal;
    file << Name("spectrum") << spectrum;
    file << Name("sampleRate") << sampleRate;
    file << Name("nfft") << nfft;

    cout << "data saved to file: " << fileName << endl;

    exit(0);
}
