//
// Created by VladB on 20-Mar-21.
//

#ifndef A45_BVLAD917_REPOSITORY_H
#define A45_BVLAD917_REPOSITORY_H


#include "../dynamic_array/dynamic_vector.h"
#include "../domain/trench_coat.h"

class Repository {
protected:
    DynamicVector<TrenchCoat> trench_coats;

public:

    /*
        Default repository constructor.
     */
    Repository();

    /*
        Find a trench coat in the repository and return it.
        Input: trench coat identifier: size - string, and colour - string
        Output: the trench coat from the repository identified by the given size and colour
        Throws: RepositoryException, if the trench coat identified by the given attributes could not
            be found in the repository
     */
    virtual TrenchCoat find_trench_coat(std::string &size, std::string &colour);

    /*
        Add a new trench coat to the repository.
        Input: reference to a trench coat
        Throws: RepositoryException, if the given trench coat is already in the repository
     */
    virtual void add_trench_to_repo(const TrenchCoat &t);

    /*
        Remove a trench coat from the repository.
        Input: reference to a trench coat.
        Throws: RepositoryException, if the given trench coat is not in the repository
     */
    virtual void remove_trench_from_repo(TrenchCoat &t);

    /*
        Update a trench coat from the repository.
        Input: reference to a trench coat.
        Throws: RepositoryException, if the given trench coat is not in the repository
     */
    virtual void update_trench_in_repo(TrenchCoat &t);

    /*
        Return the number of trench coat in the repository as an integer
     */
    virtual int get_repository_size();

    /*
        Return the repository trench coats in a dynamic array.
     */
    virtual DynamicVector<TrenchCoat> get_repository_trenches();

};


#endif //A45_BVLAD917_REPOSITORY_H
