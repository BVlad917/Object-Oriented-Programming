//
// Created by VladB on 25-May-21.
//

#include "action_add.h"

ActionAdd::ActionAdd(AbstractRepository &repo, TrenchCoat &added_coat) : repo{repo}, added_coat{added_coat} {}

void ActionAdd::execute_undo() {
    this->repo.remove_trench_from_repo(this->added_coat);
}

void ActionAdd::execute_redo() {
    this->repo.add_trench_to_repo(this->added_coat);
}


