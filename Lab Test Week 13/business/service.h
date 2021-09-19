//
// Created by VladB on 24-May-21.
//

#ifndef T3_BVLAD917_SERVICE_H
#define T3_BVLAD917_SERVICE_H


#include "../persistency/repository.h"

class Service {
private:
    Repository& repo;

public:
    explicit Service(Repository& repo);

    std::vector<TimeInterval> srv_get_all_times();

    std::vector<TimeInterval> srv_filter_by_probability(int p);

    std::vector<TimeInterval> srv_filter_by_description(std::string& desc);

    std::vector<std::string> srv_get_all_descriptions();
};


#endif //T3_BVLAD917_SERVICE_H
