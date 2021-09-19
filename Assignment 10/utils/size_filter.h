//
// Created by VladB on 16-Apr-21.
//

#ifndef A67_BVLAD917_SIZE_FILTER_H
#define A67_BVLAD917_SIZE_FILTER_H

class SizeFilter: public AbstractFilter {
    private:
        std::string size{};

    public:
        explicit SizeFilter(std::string s): size(s) { for (auto &c: this->size) c = toupper(c); };

        bool include(const TrenchCoat &t) const override { return this->size.length() == 0 || t.get_trench_size() == this->size; }
};

#endif //A67_BVLAD917_SIZE_FILTER_H
