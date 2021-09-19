//
// Created by VladB on 25-May-21.
//

#ifndef A10_BVLAD917_1_ABSTRACT_ACTION_H
#define A10_BVLAD917_1_ABSTRACT_ACTION_H


class AbstractAction {
public:
    virtual void execute_undo() = 0;

    virtual void execute_redo() = 0;

    virtual ~AbstractAction() = default;
};


#endif //A10_BVLAD917_1_ABSTRACT_ACTION_H
