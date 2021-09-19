//
// Created by VladB on 25-May-21.
//

#ifndef A10_BVLAD917_1_ACTION_UPDATE_H
#define A10_BVLAD917_1_ACTION_UPDATE_H


#include <abstract_repository.h>
#include "abstract_action.h"

class ActionUpdate : public AbstractAction {
private:
    AbstractRepository &repo;
    TrenchCoat old_coat;
    TrenchCoat new_coat;

public:
    ActionUpdate(AbstractRepository &repo, TrenchCoat &old_coat, TrenchCoat &new_coat);

    void execute_undo() override;

    void execute_redo() override;
};


#endif //A10_BVLAD917_1_ACTION_UPDATE_H
