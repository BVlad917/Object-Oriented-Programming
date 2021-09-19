//
// Created by VladB on 17-Apr-21.
//

#ifndef A67_BVLAD917_BASKET_HTML_REPO_H
#define A67_BVLAD917_BASKET_HTML_REPO_H

#include "basket_file_repo.h"

class BasketHTMLRepo : public BasketFileRepo {
protected:
    void read_from_file() override;

    void write_to_file() override;

public:
    explicit BasketHTMLRepo(std::string &file_name);
};


#endif //A67_BVLAD917_BASKET_HTML_REPO_H
