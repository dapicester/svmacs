#include "testUtils.h"
#include "boost/lexical_cast.hpp"

void
print(const std::string& msg) {
  std::cout << msg << std::endl;
}

void
print(const std::string& name, const itpp::vec& input) {
  std::cout << "\n" << name << ": " << input << std::endl;
}

void
print(const std::string& name, const itpp::mat& input) {
  std::cout << "\n" << name << ": " << input << std::endl;
}

const int DEFAULT_LENGTH = 128;

itpp::vec getTime(const double& start,
                  const double& end,
                  const double& step) {
    std::string s;
    if (step != 1.0) {
        s = boost::lexical_cast<std::string>(start)
          + ":" + boost::lexical_cast<std::string>(step)
          + ":" + boost::lexical_cast<std::string>(end) ;
    } else {
        s = boost::lexical_cast<std::string>(start)
          + ":" + boost::lexical_cast<std::string>(end) ;
    }

    itpp::vec out(s);
    return out;
}

itpp::vec getSilence() {
    itpp::vec silence(DEFAULT_LENGTH);
    silence.zeros();
    return silence;
}

itpp::vec getSilence(const itpp::vec& time) {
    itpp::vec silence(time.size());
    silence.zeros();
    return silence;
}

itpp::vec getSignal(const double& frequency, const double& noise) {
    const itpp::vec time = getTime(0, DEFAULT_LENGTH);
    return getSignal(time, frequency, noise);
}

itpp::vec getSignal(const itpp::vec& time,
                    const double& frequency,
                    const double& noise) {
    return itpp::sin(itpp::m_2pi * frequency * time ) + sqrt(noise) * itpp::randn(time.length());
}

bool equals(double a[], double b[], int length) {
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}