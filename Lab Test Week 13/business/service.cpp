//
// Created by VladB on 24-May-21.
//

#include <set>
#include "service.h"

Service::Service(Repository &repo) : repo{repo} {}

std::vector<TimeInterval> Service::srv_get_all_times() {
    return this->repo.repo_get_all_times();
}

std::vector<TimeInterval> Service::srv_filter_by_probability(int p) {
    std::vector<TimeInterval> filtered;
    for (auto &time: this->repo.repo_get_all_times()) {
        if (time.getProbability() <= p) {
            filtered.push_back(time);
        }
    }
    return filtered;
}

std::vector<TimeInterval> Service::srv_filter_by_description(std::string &desc) {
    std::vector<TimeInterval> filtered;
    for (auto &time: this->repo.repo_get_all_times()) {
        if (time.getDescription() == desc) {
            filtered.push_back(time);
        }
    }
    return filtered;
}

std::vector<std::string> Service::srv_get_all_descriptions() {
    std::vector<std::string> descriptions;
    std::set<std::string> descs;
    for (auto& t: this->repo.repo_get_all_times()) {
        descs.insert(t.getDescription());
    }
    descriptions.assign(descs.begin(), descs.end());
    return descriptions;
}
