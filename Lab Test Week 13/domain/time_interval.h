//
// Created by VladB on 24-May-21.
//

#ifndef T3_BVLAD917_TIME_INTERVAL_H
#define T3_BVLAD917_TIME_INTERVAL_H


#include <string>

class TimeInterval {
private:
    int start;
    int end;
    int probability;
    std::string description;

public:
    TimeInterval() = default;

    TimeInterval(int s, int e, int p, std::string& desc);

    int getStart() const;

    int getAnEnd() const;

    int getProbability() const;

    const std::string &getDescription() const;

    friend std::istream &operator>>(std::istream &in, TimeInterval &t);
};


#endif //T3_BVLAD917_TIME_INTERVAL_H
