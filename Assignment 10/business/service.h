//
// Created by VladB on 20-Mar-21.
//

#ifndef A45_BVLAD917_SERVICE_H
#define A45_BVLAD917_SERVICE_H


#include <stack>
#include <memory>
#include "../validation/trench_coat_validator.h"
#include "../utils/abstract_filter.h"
#include "../persistency/in_memory_repo.h"
#include "../persistency/basket_file_repo.h"
#include "../actions/abstract_action.h"

class Service {
private:
    std::string permissions;
    AbstractRepository &repo;
    BasketFileRepo &shopping_cart_repo;

    // Two stacks: One for keeping the undo operations and one for keeping the redo operations
    std::stack<std::unique_ptr<AbstractAction>> undo_stack;
    std::stack<std::unique_ptr<AbstractAction>> redo_stack;

    // Additional two stacks: One for keeping the undo operations for the shopping cart and the other for keeping
    // the redo operations for the shopping cart (So we have a separately undo-redo functionality for the
    // shopping cart)
    std::stack<std::unique_ptr<AbstractAction>> undo_cart_stack;
    std::stack<std::unique_ptr<AbstractAction>> redo_cart_stack;

public:
    /*
        Service constructor.
        Input:  - reference to an AbstractRepository object (repository for the store repository)
                - reference to a BasketFileRepo object (repository for the shopping basket)
        Output: the service object is instantiated
     */
    explicit Service(AbstractRepository &repo, BasketFileRepo &cart);

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
    std::vector<TrenchCoat> get_all_trenches_from_repo();

    /*
        Return a dynamic array containing all the trench coats from the shopping cart repository.
     */
    std::vector<TrenchCoat> get_all_trenches_from_shopping_cart();

    /*
        Adds the given trench coat in the shopping cart.
     */
    void put_trench_in_shopping_cart(TrenchCoat &t);

    /*
     * Removes the trench coat from the given index from the shopping basket.
     */
    void remove_trench_from_shopping_cart(TrenchCoat& t);

    /*
        Returns the total price from the shopping cart.
     */
    double get_total_price();

    /*
        Return a dynamic array containing all the trench coats that satisfy the condition given by <filter>.
        Input: filter - Instance of a derived class of the abstract class <AbstractFilter>
     */
    std::vector<TrenchCoat> filter_by(const AbstractFilter &filter);

    /*
        Open the file where the shopping basket items are stored.
     */
    void open_shopping_basket_file();

    /*
        Fills the repository with 10 trench coats. Used just for demonstration purposes.
     */
    void fill_repo(const std::string &fill_file_name = "populate_repo.txt");

    /*
     * Executes an undo operation in the admin mode (So for adding a new coat to the repository, for removing it,
     * or for updating it). If the stack which keeps the undo operations is empty, then a
     * ServiceException will be thrown.
     */
    void admin_undo();

    /*
     * Executes a redo operation in the admin mode (So for adding a new coat to the repository, for removing it,
     * or for updating it). If the stack which keeps the redo operations is empty, then a ServiceException
     * will be thrown
     */
    void admin_redo();

    /*
     * Executes an undo operation in the user mode (So for adding an existing coat to the shopping cart or
     * for removing a coat from the shopping cart). If the stack which keeps the undo operations is empty, then a
     * ServiceException will be thrown.
     */
    void user_undo();

    /*
     * Executes a redo operation in the user mode (So for adding an existing coat to the shopping cart or
     * for removing a coat from the shopping cart). If the stack which keeps the redo operations is empty, then a
     * ServiceException will be thrown.
     */
    void user_redo();


};


#endif //A45_BVLAD917_SERVICE_H
