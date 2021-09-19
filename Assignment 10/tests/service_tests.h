//
// Created by VladB on 20-Mar-21.
//

#ifndef A45_BVLAD917_SERVICE_TESTS_H
#define A45_BVLAD917_SERVICE_TESTS_H


class ServiceTests {
private:
    static void test_service_add();

    static void test_service_remove();

    static void test_service_update();

    static void test_get_all_trenches_from_repo();

    static void test_change_app_permissions();

    static void test_filter_by_size();

    static void test_fill_repo();

    static void test_shopping_cart();

    static void test_filter_class();

    static void test_service_with_csv_shopping_cart();

    static void test_service_with_html_shopping_cart();

    static void test_add_undo();

    static void test_add_redo();

    static void test_remove_undo();

    static void test_remove_redo();

    static void test_update_undo();

    static void test_update_redo();

    static void test_user_undo_redo();

public:
    static void run_all_service_tests();
};


#endif //A45_BVLAD917_SERVICE_TESTS_H
