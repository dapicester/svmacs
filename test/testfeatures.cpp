/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifdef DEBUG
#define PRINT(x) cout << #x << ": " << x <<endl;
#else
#define PRINT(x)
#endif

#include "testfeatures.h"

#include "feature.h"
#include "zcr.h"
#include "energy.h"
#include "ass.h"
using namespace features;

#include <itpp/itsignal.h>
using namespace itpp;

#include <iostream>
using namespace std;

int main() {
    vec t = "0:.01:2";
    t = t.left(t.size()-1);
    //PRINT(t);
    //PRINT(t.size());
    
    vec x = getSignal(t, 1.0, 0.1);
    //PRINT(x);
    vec y = getSilence(t);
    //PRINT(y);
    
    const int FEAT = 3;
    Feature* features[FEAT];
    
    const int SR = 100;
    features[0] = new ZCR(SR);
    features[1] = new Energy(SR);
    features[2] = new ASS(SR);
/*
    // temporal
    for (int i = 0; i < FEAT - 1; i++) {
        test(x, features[i]);
        test(y, features[i]);
    }
*/
    //spectral
    for (int i = FEAT - 1; i < FEAT; i++) {
        test(abs(fft(to_cvec(x),1024)), features[i]);
//	test(abs(fft(to_cvec(y),1024)), features[i]);
    }

    return 0;
}
