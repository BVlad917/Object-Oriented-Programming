//
// Created by VladB on 20-Mar-21.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>

#include "repository_tests.h"
#include "../errors/exceptions.h"
#include "../domain/trench_coat.h"
#include "../persistency/in_memory_repo.h"
#include "../persistency/basket_file_repo.h"
#include "../persistency/sql_repo.h"

void RepositoryTests::test_repo_add() {
    InMemoryRepo repo;
    assert(repo.get_repository_size() == 0);
    TrenchCoat t1("xxl", "blue", 175.99, 30, "link1");
    TrenchCoat t2("sm", "black", 155.99, 23, "link2");
    TrenchCoat t3("m", "white", 201.99, 5, "link3");
    repo.add_trench_to_repo(t1);
    repo.add_trench_to_repo(t2);
    repo.add_trench_to_repo(t3);
    assert(repo.get_repository_size() == 3);
    try {
        repo.add_trench_to_repo(TrenchCoat("xxl", "blue", 154.99, 6, "link4"));
        assert(false);
    }
    catch (RepositoryException&) {
        assert(true);
    }
}

void RepositoryTests::test_repo_remove() {
    InMemoryRepo repo;
    assert(repo.get_repository_size() == 0);
    TrenchCoat t1("xxl", "blue", 175.99, 30, "link1");
    TrenchCoat t2("sm", "black", 155.99, 23, "link2");
    TrenchCoat t3("m", "white", 201.99, 5, "link3");
    repo.add_trench_to_repo(t1);
    repo.add_trench_to_repo(t2);
    repo.add_trench_to_repo(t3);
    assert(repo.get_repository_size() == 3);
    TrenchCoat remove = TrenchCoat("xxl", "blue", 123, 123, "some_link");
    repo.remove_trench_from_repo(remove);
    assert(repo.get_repository_size() == 2);
    try {
        repo.remove_trench_from_repo(remove);
        assert(false);
    }
    catch (RepositoryException&) {
        assert(true);
    }
}

void RepositoryTests::test_repo_update() {
    InMemoryRepo repo;
    assert(repo.get_repository_size() == 0);
    TrenchCoat t1("xxl", "blue", 175.99, 30, "link1");
    TrenchCoat t2("sm", "black", 155.99, 23, "link2");
    TrenchCoat t3("m", "white", 201.99, 5, "link3");
    repo.add_trench_to_repo(t1);
    repo.add_trench_to_repo(t2);
    repo.add_trench_to_repo(t3);
    assert(repo.get_repository_size() == 3);
    TrenchCoat update("xxl", "blue", 99.99, 100, "new_link");
    repo.update_trench_in_repo(update);
    assert(repo.get_repository_size() == 3);
    TrenchCoat first = repo.get_repository_trenches()[0];
    assert(first.get_trench_quantity() == 100);
    assert(fabs(first.get_trench_price() - 99.99) < 0.00001);
    assert(first.get_trench_photograph() == "new_link");
    update = TrenchCoat("s", "grey", 103.32, 7, "some_link");
    try {
        repo.update_trench_in_repo(update);
        assert(false);
    }
    catch (RepositoryException&) {
        assert(true);
    }
}

void RepositoryTests::test_get_repository_trenches() {
    InMemoryRepo repo;
    assert(repo.get_repository_size() == 0);
    TrenchCoat t1("xxl", "blue", 175.99, 30, "link1");
    TrenchCoat t2("sm", "black", 155.99, 23, "link2");
    TrenchCoat t3("m", "white", 201.99, 5, "link3");
    repo.add_trench_to_repo(t1);
    repo.add_trench_to_repo(t2);
    repo.add_trench_to_repo(t3);
    assert(repo.get_repository_size() == 3);
    std::vector<TrenchCoat> da = repo.get_repository_trenches();
    assert(da.size() == 3);
    assert(da[0] == t1);
    assert(da[1] == t2);
    assert(da[2] == t3);

    // Test the find function from repo
    std::string search_size = "xxl", search_colour = "blue";
    TrenchCoat found = repo.find_trench_coat(search_size, search_colour);
    assert(found == t1);
    try {
        search_colour = "white";
        repo.find_trench_coat(search_size, search_colour);
        assert(false);
    }
    catch (RepositoryException &e) {
        assert(true);
    }
}

void RepositoryTests::test_repeated_instances_repository() {
    std::string file_name = "test_basket_repo.txt";
    BasketFileRepo repo{file_name};
    repo.add_trench_to_repo(TrenchCoat{"xxl", "blue", 123.23, 19, "link1"});
    repo.add_trench_to_repo(TrenchCoat{"l", "beige", 119.99, 10, "link2"});
    assert(repo.get_repository_size() == 2);
    // Now test that we can add multiple instances which are equal
    repo.add_trench_to_repo(TrenchCoat{"xxl", "blue", 123.23, 19, "link1"});
    assert(repo.get_repository_size() == 3);
}

void RepositoryTests::test_file_repository_write() {
    std::string file_name = "test_store_repo.txt";
    FileRepo repo{file_name};
    // Clear the file first so that previous test runs don't interfere with the current one
    std::ofstream fout("test_store_repo.txt");
    fout << "";
    fout.close();
    TrenchCoat t1{"xxl", "beige", 123.23, 4, "link1"};
    TrenchCoat t2{"m", "black", 119.19, 5, "link2"};
    repo.add_trench_to_repo(t1);
    repo.add_trench_to_repo(t2);
    assert(repo.get_repository_size() == 2);
    assert(repo.get_repository_trenches()[0] == t1);
    assert(repo.get_repository_trenches()[1] == t2);
}

void RepositoryTests::test_file_repository_read() {
    std::ofstream fout("test_store_repo.txt");
    fout << "XXL,Blue,70.77,9,link1\n"
            "M,Green,199.99,13,link2\n"
            "S,Red,255.55,3,link3\n";
    fout.close();
    std::string file_name = "test_store_repo.txt";
    FileRepo repo{file_name};
    assert(repo.get_repository_size() == 3);
    assert(repo.get_repository_trenches()[0].get_trench_photograph() == "link1");
    assert(repo.get_repository_trenches()[1].get_trench_photograph() == "link2");
    assert(repo.get_repository_trenches()[2].get_trench_photograph() == "link3");
}

void RepositoryTests::test_file_repository_add() {
    std::string file_name = "test_store_repo.txt";
    // Clear the file first so that previous test runs don't interfere with the current one
    std::ofstream fout("test_store_repo.txt");
    fout << "";
    fout.close();
    FileRepo repo{file_name};
    repo.add_trench_to_repo(TrenchCoat{"XXL", "Beige", 80.99, 13, "link1"});
    repo.add_trench_to_repo(TrenchCoat{"L", "Blue", 13.14, 10, "link2"});
    repo.add_trench_to_repo(TrenchCoat{"M", "Green", 54.57, 20, "link3"});
    assert(repo.get_repository_size() == 3);
    // Now using another repository with the same file, test that everything was added properly
    file_name = "test_store_repo.txt";
    FileRepo second_repo{file_name};
    assert(second_repo.get_repository_size() == 3);
    assert(second_repo.get_repository_trenches()[2].get_trench_quantity() == 20);
    assert(second_repo.get_repository_trenches()[1].get_trench_photograph() == "link2");
    assert(second_repo.get_repository_trenches()[0].get_trench_size() == "XXL");
}

void RepositoryTests::test_file_repository_remove() {
    std::string file_name = "test_store_repo.txt";
    FileRepo repo{file_name};
    // Clear the file first so that previous test runs don't interfere with the current one
    std::ofstream fout("test_store_repo.txt");
    fout << "";
    fout.close();
    repo.add_trench_to_repo(TrenchCoat{"XXL", "Beige", 80.99, 13, "link1"});
    repo.add_trench_to_repo(TrenchCoat{"L", "Blue", 13.14, 10, "link2"});
    repo.add_trench_to_repo(TrenchCoat{"M", "Green", 54.57, 20, "link3"});
    assert(repo.get_repository_size() == 3);
    TrenchCoat remove{"L", "Blue", 1, 1, ""};
    repo.remove_trench_from_repo(remove);
    assert(repo.get_repository_size() == 2);
    remove = TrenchCoat{"XXL", "Beige", 1, 1, ""};
    repo.remove_trench_from_repo(remove);
    assert(repo.get_repository_size() == 1);
    assert(repo.get_repository_trenches()[0].get_trench_size() == "M");
    // Now using another repository with the same file, test that everything was removed properly
    file_name = "test_store_repo.txt";
    FileRepo second_repo{file_name};
    assert(second_repo.get_repository_size() == 1);
    assert(second_repo.get_repository_trenches()[0].get_trench_size() == "M");
}

void RepositoryTests::test_file_repository_update() {
    std::string file_name = "test_store_repo.txt";
    FileRepo repo{file_name};
    // Clear the file first so that previous test runs don't interfere with the current one
    std::ofstream fout("test_store_repo.txt");
    fout << "";
    fout.close();
    repo.add_trench_to_repo(TrenchCoat{"XXL", "Beige", 80.99, 13, "link1"});
    repo.add_trench_to_repo(TrenchCoat{"L", "Blue", 13.14, 10, "link2"});
    repo.add_trench_to_repo(TrenchCoat{"M", "Green", 54.57, 20, "link3"});
    assert(repo.get_repository_size() == 3);
    TrenchCoat update{"xxl", "beige", 100.83, 12, "link10"};
    repo.update_trench_in_repo(update);
    update = TrenchCoat{"M", "Green", 13.13, 30, "link30"};
    repo.update_trench_in_repo(update);
    // Now using another repository with the same file, test that everything was updated properly
    file_name = "test_store_repo.txt";
    FileRepo second_repo{file_name};
    assert(second_repo.get_repository_size() == 3);
    assert(second_repo.get_repository_trenches()[0].get_trench_quantity() == 12);
    assert(fabs(second_repo.get_repository_trenches()[2].get_trench_price() - 13.13) < 0.0001);
}

void RepositoryTests::test_file_repository_find() {
    std::string file_name = "test_store_repo.txt";
    FileRepo repo{file_name};
    // Clear the file first so that previous test runs don't interfere with the current one
    std::ofstream fout("test_store_repo.txt");
    fout << "";
    fout.close();
    repo.add_trench_to_repo(TrenchCoat{"XXL", "Beige", 80.99, 13, "link1"});
    repo.add_trench_to_repo(TrenchCoat{"L", "Blue", 13.14, 10, "link2"});
    repo.add_trench_to_repo(TrenchCoat{"M", "Green", 54.57, 20, "link3"});
    assert(repo.get_repository_size() == 3);
    // Now using another repository with the same file, test that we can find the coats
    file_name = "test_store_repo.txt";
    FileRepo second_repo{file_name};
    std::string search_size = "xxl", search_color = "beige";
    assert(second_repo.find_trench_coat(search_size, search_color).get_trench_quantity() == 13);
    search_size = "l", search_color = "blue";
    assert(second_repo.find_trench_coat(search_size, search_color).get_trench_photograph() == "link2");
    try {
        search_size = "s";
        second_repo.find_trench_coat(search_size, search_color);
    }
    catch (RepositoryException&) {
        assert(true);
    }
}

void RepositoryTests::test_sql_repository() {
//    std::cout << "\n\nRUNNING SQL REPO TESTS\n\n";
//    std::string file_name = "test_sql_store_repo.db";
//    SQLRepo repo{file_name};
//    TrenchCoat t1{"xxl", "black", 123.23, 12, "link1"};
//    repo.add_trench_to_repo(t1);
//    assert(repo.get_repository_size() == 1);
//    std::string searched_size = "XXL", searched_colour = "Black";
//    t1 = repo.find_trench_coat(searched_size, searched_colour);
//    assert(t1.get_trench_size() == "XXL");
//    assert(t1.get_trench_colour() == "Black");
//    assert(t1.get_trench_quantity() == 12);
//    assert(t1.get_trench_photograph() == "link1");
//
//    t1 = TrenchCoat{"xxl", "black", 1, 1, "dummy_link"};
//    repo.remove_trench_from_repo(t1);
//    assert(repo.get_repository_size() == 0);

//    t1 = TrenchCoat{"xxl", "black", 123.23, 12, "link1"};
//    repo.add_trench_to_repo(t1);
//    t1 = TrenchCoat{"xs", "blue", 199.99, 13, "link2"};
//    repo.add_trench_to_repo(t1);
//    t1 = TrenchCoat{"m", "midnight", 99.99, 14, "link3"};
//    repo.add_trench_to_repo(t1);
//    assert(repo.get_repository_size() == 3);
//    TrenchCoat t1 = TrenchCoat{"xs", "blue", 10.3, 200, "link99"};
//    repo.update_trench_in_repo(t1);
//    std::string searched_size = "xs", searched_colour = "blue";
//    t1 = repo.find_trench_coat(searched_size, searched_colour);
//    assert(t1.get_trench_quantity() == 200);
//    assert(t1.get_trench_photograph() == "link99");
//
//    std::cout << "\n\nRAN SQL REPO TESTS\n\n";
}

void RepositoryTests::run_all_repo_tests() {
    test_repo_add();
    test_repo_remove();
    test_repo_update();
    test_get_repository_trenches();
    test_repeated_instances_repository();
    test_file_repository_write();
    test_file_repository_read();
    test_file_repository_add();
    test_file_repository_remove();
    test_file_repository_update();
    test_file_repository_find();
    test_sql_repository();
}
