#include "testUtils.h"

void
print(const std::string& name, const itpp::vec& input) {
  std::cout << "\n" << name << ": " << input << std::endl;
}

void
print(const std::string& name, const itpp::mat& input) {
  std::cout << "\n" << name << ": " << input << std::endl;
}

const int DEFAULT_LENGTH = 128;

itpp::vec getTime(const double start, const double end, const double step = 1) {
    std::string s;
    if (step != 1) {
        s = utils::stringify(start) 
          + ":" + utils::stringify(step) 
          + ":" + utils::stringify(end) ;
    } else {
        s = utils::stringify(start) 
          + ":" + utils::stringify(end) ;
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

itpp::vec getSignal() {
    const itpp::vec time = getTime(0, DEFAULT_LENGTH);
    return getSignal(time);
}

itpp::vec getSignal(const itpp::vec& time) {
    const double noise = 0.0;
    const double frequency = 1.0;
    return itpp::sin(itpp::m_2pi * frequency * time ) + sqrt(noise) * itpp::randn(time.length());
}
