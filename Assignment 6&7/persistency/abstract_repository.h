//
// Created by VladB on 17-Apr-21.
//

#ifndef A67_BVLAD917_ABSTRACT_REPOSITORY_H
#define A67_BVLAD917_ABSTRACT_REPOSITORY_H

#include "../domain/trench_coat.h"

class AbstractRepository {
public:
    /*
        Virtual repository destructor. Allows polymorphic behaviour, if needed.
     */
    virtual ~AbstractRepository() = default;

    /*
        Find a trench coat in the repository and return it.
        Input: trench coat identifier: size - string, and colour - string
        Output: the trench coat from the repository identified by the given size and colour
        Throws: RepositoryException, if the trench coat identified by the given attributes could not
            be found in the repository
     */
    virtual TrenchCoat find_trench_coat(std::string &size, std::string &colour) = 0;

    /*
        Add a new trench coat to the repository.
        Input: reference to a trench coat
        Throws: RepositoryException, if the given trench coat is already in the repository
     */
    virtual void add_trench_to_repo(const TrenchCoat &t) = 0;

    /*
        Remove a trench coat from the repository.
        Input: reference to a trench coat.
        Throws: RepositoryException, if the given trench coat is not in the repository
     */
    virtual void remove_trench_from_repo(TrenchCoat &t) = 0;

    /*
        Update a trench coat from the repository.
        Input: reference to a trench coat.
        Throws: RepositoryException, if the given trench coat is not in the repository
     */
    virtual void update_trench_in_repo(TrenchCoat &t) = 0;

    /*
        Return the number of trench coat in the repository as an integer
     */
    virtual int get_repository_size() = 0;

    /*
        Return the repository trench coats in a dynamic array.
     */
    virtual std::vector<TrenchCoat> get_repository_trenches() = 0;
};

#endif //A67_BVLAD917_ABSTRACT_REPOSITORY_H
