//
// Created by VladB on 24-May-21.
//

#include <vector>
#include <sstream>
#include "time_interval.h"

TimeInterval::TimeInterval(int s, int e, int p, std::string& desc): start{s}, end{e}, probability{p}, description{desc} {}

int TimeInterval::getStart() const {
    return start;
}

int TimeInterval::getAnEnd() const {
    return end;
}

int TimeInterval::getProbability() const {
    return probability;
}

const std::string &TimeInterval::getDescription() const {
    return description;
}

std::vector<std::string> tokenize(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::istream &operator>>(std::istream &in, TimeInterval &t) {
    std::string line;
    std::getline(in, line);
    std::vector<std::string> tokens = tokenize(line, ';');
    if (tokens.size() != 4) {
        return in;
    }
    t.start = std::stoi(tokens[0]);
    t.end = std::stoi(tokens[1]);
    t.probability = std::stoi(tokens[2]);
    t.description = tokens[3];
    return in;
}
