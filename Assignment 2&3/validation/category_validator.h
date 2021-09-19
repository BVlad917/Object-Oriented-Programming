//
// Created by VladB on 12-Mar-21.
//

#ifndef A23_BVLAD917_CATEGORY_VALIDATOR_H
#define A23_BVLAD917_CATEGORY_VALIDATOR_H

/// Checks if the given category is a valid one. It is valid if the category exists (so it's in the interval
/// [1, 4]) OR if category = -1. This second part is because we need a way to signal to the program the concept
/// of ALL CATEGORIES. We use the convention that if -1 is passed as category, this means all categories.
/// \param category: the category to be validated; integer
/// \return 0 if the given category is valid; -1 otherwise
int validate_category(int category);

#endif //A23_BVLAD917_CATEGORY_VALIDATOR_H
