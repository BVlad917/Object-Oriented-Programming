//
// Created by VladB on 25-May-21.
//

#include "action_remove.h"

ActionRemove::ActionRemove(AbstractRepository &repo, TrenchCoat &coat): repo{repo}, removed_coat{coat} {}

void ActionRemove::execute_undo() {
    this->repo.add_trench_to_repo(this->removed_coat);
}

void ActionRemove::execute_redo() {
    this->repo.remove_trench_from_repo(this->removed_coat);
}
