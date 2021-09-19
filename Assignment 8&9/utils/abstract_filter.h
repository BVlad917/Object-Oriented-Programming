//
// Created by VladB on 16-Apr-21.
//

#ifndef A67_BVLAD917_ABSTRACT_FILTER_H
#define A67_BVLAD917_ABSTRACT_FILTER_H

class AbstractFilter {
    public:
        virtual bool include(const TrenchCoat &t) const = 0;
};

#endif //A67_BVLAD917_ABSTRACT_FILTER_H
