/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_RANGE_H
#define SVMACS_RANGE_H

#include "config.h"
#include <itpp/itbase.h>
#include <itpp/base/operators.h>

NS_SVMACS_BEGIN

/**
 * Linearly scale matrix rows to be whithin a given range.
 * @param input The matrix to be scaled, having size (N,M).
 * @param range The range matrix, having (2,M) whose rows contain
 *              respectively the min and max value.
 * @return A new matrix with scaled data.
 */
// FIXME: unit test fails!!
inline itpp::mat
scaleData(const itpp::mat& input, const itpp::mat& range) {
    int R = input.rows();
    int C = input.cols();

    itpp::mat scaled(R,C);
    scaled.zeros();

    // scale data to be within [mi,Mi]
    itpp::vec col;
    double mi, Mi;
    for(int i = 0; i < C; i++) {
        col = input.get_col(i);

        mi = range(0,i);
        Mi = range(1,i);
        if( (Mi - mi) != 0.0) {
            itpp::vec value = 2 * (col - mi ) / (Mi - mi) - 1; // FIXME: declare outside
            scaled.set_col(i, value);
        }
    }
    return scaled;
}
/**
 * Linearly scale vector values to be whithin a given range.
 * @param input The vector to be scaled, having size (1,N).
 * @param range The range matrix, having (2,N) whose rows contain
 *              respectively the min and max value.
 * @return A new vector with scaled data.
 */

inline itpp::vec
scaleData(const itpp::vec& input, const itpp::mat& range) {
    const int len = input.length();

    itpp::vec scaled(len);
    scaled.zeros();

    // scale data to be within [mi,Mi]
    double mi, Mi;
    for(int i = 0; i < len; i++) {
        mi = range(0,i);
        Mi = range(1,i);
        if( (Mi - mi) != 0.0) {
            scaled[i] = 2 * (input[i] - mi ) / (Mi - mi) - 1;
        }
    }
    return scaled;
}

/**
 * The range matrix used by the SVM classifier.
 */
const itpp::mat Range = //TODO: salvare in un file IT++ ?
    " 677.1070780399273871807963587343692779541015625 "
    " 171.124029237493601840469636954367160797119140625 "
    "2600.723774908210543799214065074920654296875 "
    "  59.69150951247078040751148364506661891937255859375 "
    "  21.059999999999998721023075631819665431976318359375 "
    "   0.267689280960842435064250821596942842006683349609375 "
    "  -7.74125676741966106675363334943540394306182861328125 "
    "  -8.6084652225091371491316749597899615764617919921875 "
    "  -5.40178042983103523511090315878391265869140625 "
    "  -3.437045997456957824311984950327314436435699462890625 "
    "  -2.05819146326689317305635995580814778804779052734375 "
    "  -2.2630848108924652706264168955385684967041015625 "
    ";"
    "14839.193561114176191040314733982086181640625 "
    "  615.9148618438683797648991458117961883544921875 "
    "21444.23623916276847012341022491455078125 "
    "  302.631344025779753792448900640010833740234375 "
    "  458.13043478260868823781493119895458221435546875 "
    "    0.9619978068740582255458093641209416091442108154296875 "
    "    6.52677504115817708196800595032982528209686279296875 "
    "    1.7837935490615108857781478945980779826641082763671875 "
    "    3.216453257954920541550336565705947577953338623046875 "
    "    3.56360255575086437573872899520210921764373779296875 "
    "    2.75483162225700795033844769932329654693603515625 "
    "    2.1050579205616930522637630929239094257354736328125 ";

NS_SVMACS_END

#endif // SVMACS_RANGE_H
