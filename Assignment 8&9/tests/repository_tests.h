//
// Created by VladB on 20-Mar-21.
//

#ifndef A45_BVLAD917_REPOSITORY_TESTS_H
#define A45_BVLAD917_REPOSITORY_TESTS_H


class RepositoryTests {
private:
    static void test_repo_add();

    static void test_repo_remove();

    static void test_repo_update();

    static void test_get_repository_trenches();

    static void test_repeated_instances_repository();

    static void test_file_repository_write();

    static void test_file_repository_read();

    static void test_file_repository_add();

    static void test_file_repository_remove();

    static void test_file_repository_update();

    static void test_file_repository_find();

    static void test_sql_repository();

public:
    static void run_all_repo_tests();
};


#endif //A45_BVLAD917_REPOSITORY_TESTS_H
