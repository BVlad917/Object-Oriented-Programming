//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_BUILDING_H
#define E2_BVLAD917_BUILDING_H


#include <string>
#include <vector>

class Building {
private:
    int id{};
    std::string description;
    std::string thematicArea;
    std::vector<std::string> location;

public:
    Building() = default;

    Building(int id, std::string desc, std::string ta, std::vector<std::string> loc);

    int getId() const;

    const std::string &getDescription() const;

    const std::string &getThematicArea() const;

    const std::vector<std::string> &getLocation() const;

    friend std::istream &operator>>(std::istream &in, Building &p);

    bool operator==(const Building &other) const;

};


#endif //E2_BVLAD917_BUILDING_H
