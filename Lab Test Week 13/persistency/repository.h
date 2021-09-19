//
// Created by VladB on 24-May-21.
//

#ifndef T3_BVLAD917_REPOSITORY_H
#define T3_BVLAD917_REPOSITORY_H


#include <vector>
#include "../domain/time_interval.h"

class Repository {
private:
    std::vector<TimeInterval> all_times;
    std::string file_name;

    void read_file();

public:
    explicit Repository(std::string fn);

    std::vector<TimeInterval> repo_get_all_times();
};


#endif //T3_BVLAD917_REPOSITORY_H
