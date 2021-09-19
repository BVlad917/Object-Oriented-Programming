#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//
// Created by VladB on 19-Mar-21.
//

#include <iostream>
#include <QApplication>
#include <QFile>
#include <fstream>
#include <sstream>
#include <memory>

#include "tests/all_tests.h"
#include "business/service.h"
#include "presentation/ui.h"
#include "persistency/basket_csv_repo.h"
#include "persistency/basket_html_repo.h"
#include "persistency/sql_repo.h"
#include "presentation/gui.h"
#include "settings_handler/settings_handler.h"
#include "errors/exceptions.h"

int main(int argc, char *argv[]) {
    AllTests::void_run_all_tests();

    try {
        SettingsHandler sh{"settings.properties"};

        if (sh.is_gui()) {
            QApplication app{argc, argv};
            QFile style_sheet_file("./Toolery.qss");
            style_sheet_file.open(QFile::ReadOnly);
            QString style_sheet = QLatin1String(style_sheet_file.readAll());
            app.setStyleSheet(style_sheet);

            std::unique_ptr<AbstractRepository> store_repo;
            std::unique_ptr<BasketFileRepo> basket_repo;
            if (sh.get_store_repo_type() == "database") {
                std::string sql_store_repo_file = sh.get_store_repo_file();
                store_repo = std::make_unique<SQLRepo>(sql_store_repo_file);
            } else if (sh.get_store_repo_type() == "text") {
                std::string text_store_repo_file = sh.get_store_repo_file();
                store_repo = std::make_unique<FileRepo>(text_store_repo_file);
            } else if (sh.get_store_repo_type() == "inmemory") {
                store_repo = std::make_unique<InMemoryRepo>();
            }

            if (sh.get_basket_repo_type() == "CSV") {
                std::string csv_basket_repo_file = sh.get_basket_repo_file();
                basket_repo = std::make_unique<BasketCSVRepo>(csv_basket_repo_file);
            } else if (sh.get_basket_repo_type() == "HTML") {
                std::string html_basket_repo_file = sh.get_basket_repo_file();
                basket_repo = std::make_unique<BasketHTMLRepo>(html_basket_repo_file);
            }

            std::unique_ptr<Service> srv = std::make_unique<Service>(*store_repo, *basket_repo);
            GUI gui{*srv};
            gui.show();
            return app.exec();
        } else {
            AbstractRepository* store_repo;
            BasketFileRepo* basket_repo;
            if (sh.get_store_repo_type() == "database") {
                std::string sql_store_repo_file = sh.get_store_repo_file();
                store_repo = new SQLRepo{sql_store_repo_file};
            } else if (sh.get_store_repo_type() == "text") {
                std::string text_store_repo_file = sh.get_store_repo_file();
                store_repo = new FileRepo{text_store_repo_file};
            } else if (sh.get_store_repo_type() == "inmemory") {
                store_repo = new InMemoryRepo{};
            }

            if (sh.get_basket_repo_type() == "CSV") {
                std::string csv_basket_repo_file = sh.get_basket_repo_file();
                basket_repo = new BasketCSVRepo{csv_basket_repo_file};
            } else if (sh.get_basket_repo_type() == "HTML") {
                std::string html_basket_repo_file = sh.get_basket_repo_file();
                basket_repo = new BasketHTMLRepo{html_basket_repo_file};
            }

            Service srv{*store_repo, *basket_repo};
            UI ui{srv};
            ui.run_app();
            // delete the components
            delete store_repo;
            delete basket_repo;

            return 0;
        }
    }
    catch (SettingsException &se) {
        std::cout << se.what();
        return 1;
    }
}

#pragma clang diagnostic pop