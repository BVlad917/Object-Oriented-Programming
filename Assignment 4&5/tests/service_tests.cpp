//
// Created by VladB on 20-Mar-21.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include "service_tests.h"
#include "../persistency/repository.h"
#include "../business/service.h"

void ServiceTests::test_service_add() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    srv.add_trench("xxl", "black", 123.34, 15, "link1");
    assert(srv.get_all_trenches_from_repo().get_dynamic_vector_size() == 1);
    assert(repo.get_repository_trenches().get_dynamic_vector_size() == 1);
    try {
        srv.add_trench("invalid", "white", -132.32, 11, "link2");
        assert(false);
    }
    catch (ValidationException &e) {
        assert(true);
    }
}

void ServiceTests::test_service_remove() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    srv.add_trench("xxl", "black", 123.34, 15, "link1");
    srv.add_trench("s", "white", 199.99, 7, "link2");
    srv.remove_trench("s", "white");
    assert(srv.get_all_trenches_from_repo().get_dynamic_vector_size() == 1);
    try {
        srv.remove_trench("xl", "black");
        assert(false);
    }
    catch (RepositoryException &e) {
        assert(true);
    }
}

void ServiceTests::test_service_update() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    srv.add_trench("xxl", "black", 123.34, 15, "link1");
    srv.add_trench("s", "white", 199.99, 7, "link2");
    srv.update_trench("xxl", "black", 100.07, 10, "link9");
    TrenchCoat updated_trench_coat = srv.get_all_trenches_from_repo()[0];
    assert(fabs(updated_trench_coat.get_trench_price() - 100.07) < 0.0001);
    assert(updated_trench_coat.get_trench_quantity() == 10);
    assert(updated_trench_coat.get_trench_photograph() == "link9");
    assert(srv.get_all_trenches_from_repo().get_dynamic_vector_size() == 2);
    try {
        srv.update_trench("s", "blue", 99.99, 10, "link3");
        assert(false);
    }
    catch (RepositoryException &e) {
        assert(true);
    }
}

void ServiceTests::test_get_all_trenches_from_repo() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    srv.add_trench("xxl", "black", 123.34, 15, "link1");
    srv.add_trench("s", "white", 199.99, 7, "link2");
    DynamicVector<TrenchCoat> da = srv.get_all_trenches_from_repo();
    assert(da.get_dynamic_vector_size() == 2);
    assert(da.get_dynamic_vector_elements()[0].get_trench_quantity() == 15);
    assert(da.get_dynamic_vector_elements()[1].get_trench_quantity() == 7);
}

void ServiceTests::test_change_app_permissions() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    // The permissions are defaulted to "User" permissions
    assert(srv.get_app_permissions() == "User");
    srv.change_app_permissions("Admin");
    assert(srv.get_app_permissions() == "Admin");
    try {
        srv.change_app_permissions("Friend");
        assert(false);
    }
    catch (ServiceException &e) {
        assert(true);
    }
}

void ServiceTests::test_filter_by_size() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    srv.add_trench("xxl", "black", 123.34, 15, "link1");
    srv.add_trench("s", "white", 199.99, 7, "link2");
    srv.add_trench("xxl", "beige", 101.1, 12, "link3");
    srv.add_trench("s", "green", 109.32, 19, "link4");
    srv.add_trench("m", "red", 189.76, 9, "link5");
    DynamicVector<TrenchCoat> filtered_xxl = srv.filter_by_size("xxl");
    assert(filtered_xxl.get_dynamic_vector_size() == 2);
    assert(filtered_xxl.find_position_of_elem(TrenchCoat("xxl", "black", 101, 101, "")) == 0);
    assert(filtered_xxl.find_position_of_elem(TrenchCoat("xxl", "beige", 101, 101, "")) == 1);
    DynamicVector<TrenchCoat> no_filter = srv.filter_by_size("");
    assert(no_filter.get_dynamic_vector_size() == 5);
}

void ServiceTests::test_fill_repo() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    srv.fill_repo();
    assert(srv.get_all_trenches_from_repo().get_dynamic_vector_size() == 10);
}

void ServiceTests::test_shopping_cart() {
    Repository repo;
    RepeatedInstancesRepository shopping_cart;
    Service srv(repo, shopping_cart);
    TrenchCoat t1{"xxl", "blue", 123.23, 14, "link1"};
    TrenchCoat t2{"m", "beige", 142.19, 3, "link2"};
    repo.add_trench_to_repo(t1);
    repo.add_trench_to_repo(t2);
    srv.put_trench_in_shopping_cart(t1);
    srv.put_trench_in_shopping_cart(t2);
    assert(fabs(srv.get_total_price() - (123.23 + 142.19)) < 0.0001);
    DynamicVector<TrenchCoat> shopping_cart_coats = srv.get_all_trenches_from_shopping_cart();
    assert(shopping_cart_coats.get_dynamic_vector_size() == 2);
    assert(shopping_cart_coats[0] == t1);
    assert(shopping_cart_coats[1] == t2);

    // Remove a trench coat from the store and see that it is also automatically removed from the shopping cart
    srv.remove_trench("xxl", "blue");
    assert(repo.get_repository_size() == 1);
    assert(shopping_cart.get_repository_size() == 1);
    shopping_cart.remove_trench_from_repo(t2);
    assert(shopping_cart.get_repository_size() == 0);
    assert(repo.get_repository_size() == 1);

    // Test that we can't add to the shopping cart more of the same coat than there are in the shop
    srv.put_trench_in_shopping_cart(t2);
    srv.put_trench_in_shopping_cart(t2);
    srv.put_trench_in_shopping_cart(t2);
    assert(shopping_cart.get_repository_size() == 3);
    try {
        srv.put_trench_in_shopping_cart(t2);
        assert(false);
    }
    catch (ServiceException&) {
        assert(true);
    }
}

void ServiceTests::run_all_service_tests() {
    test_service_add();
    test_service_remove();
    test_service_update();
    test_get_all_trenches_from_repo();
    test_change_app_permissions();
    test_filter_by_size();
    test_fill_repo();
    test_shopping_cart();
}

