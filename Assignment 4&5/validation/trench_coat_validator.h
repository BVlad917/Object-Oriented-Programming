//
// Created by VladB on 20-Mar-21.
//

#ifndef A45_BVLAD917_TRENCH_COAT_VALIDATOR_H
#define A45_BVLAD917_TRENCH_COAT_VALIDATOR_H


#include "../domain/trench_coat.h"

class TrenchCoatValidator {
public:
    /*
        Validate the attributes of a created trench coat.
        Throws: ValidationException if any of the trench coat attributes are invalid.
     */
    static void validate(TrenchCoat &t);
};


#endif //A45_BVLAD917_TRENCH_COAT_VALIDATOR_H
