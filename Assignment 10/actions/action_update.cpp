//
// Created by VladB on 25-May-21.
//

#include "action_update.h"

ActionUpdate::ActionUpdate(AbstractRepository &repo, TrenchCoat &old_coat, TrenchCoat &new_coat)
        : repo{repo}, old_coat{old_coat}, new_coat{new_coat} {}

void ActionUpdate::execute_undo() {
    this->repo.update_trench_in_repo(this->old_coat);
}

void ActionUpdate::execute_redo() {
    this->repo.update_trench_in_repo(this->new_coat);
}

