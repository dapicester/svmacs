/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "svmclassifier.h"
#include "model/range.h"

#include <itpp/itbase.h>

#define RLOG_COMPONENT "svmclassifier"
#include <rlog/rlog.h>

NS_SVMACS_BEGIN

using std::string;

SvmClassifier::SvmClassifier(const string& dmodel, const string& cmodel) {
    rInfo("loading Detection model %s ...", dmodel.c_str());
    m1.reset(readModel(dmodel));

    rInfo("loading Classification model %s ...", cmodel.c_str());
    model.reset(readModel(cmodel));

    rInfo("SvmClassifier created");
}

SvmClassifier::~SvmClassifier(){
    rInfo("SvmClassifier correctly destroyed");
}

svm_model*
SvmClassifier::readModel(const string& name) {
    svm_model* model = svm_load_model(name.c_str());
    if (model == NULL) {
        string message = "Model " + name + " is NULL!";
        rError("%s", message.c_str());
        throw BadModel(message);
    }
    rDebug("loaded model file: %s", name.c_str());
    return model;
}

Event::Type
SvmClassifier::classify(const itpp::vec& features) const {
    //rDebug("feature vector: %s", itpp::to_str(features).c_str());

    rDebug("scaling data");
    itpp::vec scaled = scaleData(features, Range);

    //rDebug("scaled vector: %s", itpp::to_str(scaled).c_str());

    // build the array for libsvm
    const int len = scaled.length();
    svm_node array[len + 1];

    int i = 0;
    while (i < len) {
         array[i].index = i + 1;
         array[i].value = scaled[i];
         i++;
    }
    // mark the last element
    array[i].index = -1;
    array[i].value = 0.0;

#if 0
    for (int i=0; i<len+1; i++) {
       rDebug("array[%d]:  index=%d  value=%f", i, array[i].index, array[i].value);
    }
#endif

#if 1 /* enable/disable detection step */
    int detected = svm_predict(m1.get(), array);
    rDebug("detection = %s", (detected == 1) ? "yes" : "no");
#else /* classification without detection */
    int detected = 1;
#endif

#if 1 /* enable/disable classification step */
    if (detected == 1) {
        int type = svm_predict(model.get(), array);
        rDebug("classification = %d", type);
        if (type != 0) {
            return static_cast<Event::Type>(type);
        }
    }
#endif

    return Event::NONE;
}

NS_SVMACS_END
