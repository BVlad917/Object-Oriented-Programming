//
// Created by VladB on 25-May-21.
//

#ifndef A10_BVLAD917_1_ACTION_ADD_H
#define A10_BVLAD917_1_ACTION_ADD_H


#include "abstract_action.h"
#include "../persistency/abstract_repository.h"

class ActionAdd : public AbstractAction {
private:
    AbstractRepository &repo;
    TrenchCoat added_coat;

public:
    ActionAdd(AbstractRepository& repo, TrenchCoat& added_coat);

    void execute_undo() override;

    void execute_redo() override;

};


#endif //A10_BVLAD917_1_ACTION_ADD_H
