//
// Created by VladB on 20-Mar-21.
//

#ifndef A45_BVLAD917_SERVICE_H
#define A45_BVLAD917_SERVICE_H


#include "../persistency/repository.h"
#include "../persistency/repeated_instances_repository.h"

class Service {
private:
    Repository &repo;
    RepeatedInstancesRepository &shopping_cart_repo;
    std::string permissions;
public:
    /*
        Service constructor.
        Input: reference to a Repository object
        Output: the service object is instantiated
     */
    explicit Service(Repository &repo, RepeatedInstancesRepository &cart);

    /*
        Change the app permissions.
        Input: string with either "User" or "Admin".
        Output: the app permissions are changed
        Throws: ServiceException, if the given string is not "User" or "Admin"
     */
    void change_app_permissions(const std::string &new_permissions);

    /*
        Return the current app permissions. Returns a string which is either "User" or "Admin".
     */
    std::string get_app_permissions();

    /*
        Add a new trench coat to the repository.
        Input: trench coat properties: size (string), colour (string), price (real number),
            quantity (integer), photo link(string)
        Output: the new trench coat is added to the repository
        Throws: ValidationException, if the given attributes are not valid
     */
    void add_trench(std::string size, std::string colour, double price, int quantity, std::string photo);

    /*
        Remove a trench coat from the repository.
        Input: trench coat identifiers, meaning the size (string) and the colour (string)
        Throws: ValidationException if the given attributes are not valid; RepositoryException if the trench coat
            cannot be found in the repository
     */
    void remove_trench(std::string size, std::string colour);

    /*
        Update a trench coat from the repository.
        Input: trench coat identifiers + new trench coat attributes, meaning the size and colour (both
            strings, identifiers) + the new price (real number), quantity (integer), and photo link (string)
        Throws: ValidationException if the given attributes are not valid; RepositoryException a trench coat cannot
            be identified by the given attributes
     */
    void update_trench(std::string size, std::string colour, double price, int quantity, std::string photo);

    /*
        Return a dynamic array containing all the trench coats from the repository.
     */
    DynamicVector<TrenchCoat> get_all_trenches_from_repo();

    /*
        Return a dynamic array containing all the trench coats from the shopping cart repository.
     */
    DynamicVector<TrenchCoat> get_all_trenches_from_shopping_cart();

    /*
        Adds the given trench coat in the shopping cart.
     */
    void put_trench_in_shopping_cart(TrenchCoat& t);

    /*
        Returns the total price from the shopping cart.
     */
    double get_total_price();

    /*
        Return a dynamic array containing all the trench coats of the given size;
     */
    DynamicVector<TrenchCoat> filter_by_size(std::string size);

    /*
        Fills the repository with 10 trench coats. Used just for demonstration purposes.
     */
    void fill_repo();
};


#endif //A45_BVLAD917_SERVICE_H
