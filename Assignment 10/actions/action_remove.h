//
// Created by VladB on 25-May-21.
//

#ifndef A10_BVLAD917_1_ACTION_REMOVE_H
#define A10_BVLAD917_1_ACTION_REMOVE_H


#include <abstract_repository.h>
#include "abstract_action.h"

class ActionRemove : public AbstractAction {
private:
    AbstractRepository& repo;
    TrenchCoat removed_coat;

public:
    ActionRemove(AbstractRepository& repo, TrenchCoat& coat);

    void execute_undo() override;

    void execute_redo() override;
};


#endif //A10_BVLAD917_1_ACTION_REMOVE_H
