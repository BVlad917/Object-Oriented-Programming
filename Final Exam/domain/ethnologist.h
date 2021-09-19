//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_ETHNOLOGIST_H
#define E2_BVLAD917_ETHNOLOGIST_H


#include <string>
#include <utility>

class Ethnologist {
private:
    std::string name;
    std::string thematicArea;

public:
    Ethnologist() = default;

    Ethnologist(std::string n, std::string ta);

    const std::string &getName() const;

    const std::string &getThematicArea() const;

    friend std::istream &operator>>(std::istream &in, Ethnologist &p);

    bool operator==(const Ethnologist &other) const;
};


#endif //E2_BVLAD917_ETHNOLOGIST_H
