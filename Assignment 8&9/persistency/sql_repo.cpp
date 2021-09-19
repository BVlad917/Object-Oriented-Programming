//
// Created by VladB on 18-Apr-21.
//

#include <vector>

#include "sql_repo.h"
#include "../errors/exceptions.h"

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
    auto* records = static_cast<Records*>(p_data);
    try {
        records->emplace_back(p_fields, p_fields + num_fields);
    }
    catch (...) {
        // abort select on failure, don't let exception propagate thru sqlite3 call-stack
        return 1;
    }
    return 0;
}

Records select_stmt(sqlite3 *db, const char* stmt)
{
    Records records;
    char *errmsg;
    int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
    if (ret != SQLITE_OK) {
        std::string stmt_str(stmt);
        std::string errmsg_str(errmsg);
        std::string error_msg = "Error in select statement " + stmt_str + "[" + errmsg_str + "]\n";
        throw RepositoryException(error_msg);
        //std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
    }
    else {
        // std::cerr << records.size() << " records returned.\n";
    }
    return records;
}

SQLRepo::SQLRepo(std::string &file_name): db_file_name(file_name) {
    int db_flag = sqlite3_open(this->db_file_name.c_str(), &this->database);
    if (db_flag) {
        throw RepositoryException("\nERROR: Could not open database.\n");
    }
    std::string sql_statement = "CREATE TABLE IF NOT EXISTS COATS ("
                                "SIZE TEXT not null,"
                                "COLOUR TEXT not null,"
                                "PRICE REAL not null,"
                                "QUANTITY INTEGER not null,"
                                "LINK TEXT not null,"
                                "PRIMARY KEY (SIZE, COLOUR),"
                                "CONSTRAINT unq UNIQUE (SIZE, COLOUR)"
                                ");";
    if (sqlite3_exec(this->database, sql_statement.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
        throw RepositoryException("\nERROR: Could not create SQL table.\n");
    }
}

SQLRepo::~SQLRepo() {
    sqlite3_close(this->database);
}

TrenchCoat SQLRepo::find_trench_coat(std::string &size, std::string &colour) {
    for (auto &c: size) c = toupper(c);
    colour[0] = toupper(colour[0]);
    for (int i = 1; i < colour.length(); i++) colour[i] = tolower(colour[i]);
    std::string sql_statement = "SELECT * FROM COATS WHERE SIZE = '" + size + "' AND COLOUR = '" + colour + "';";
    Records res = select_stmt(this->database, sql_statement.c_str());
    if (res.empty()) {
        throw RepositoryException("\nError! The trench coat is not in the store.\n");
    }
    else {
        std::vector<std::string> found = res[0];
        std::string s = found[0];
        std::string c = found[1];
        double p = std::stof(found[2]);
        int q = std::stoi(found[3]);
        std::string l = found[4];
        return TrenchCoat{s, c, p, q, l};
    }
}

void SQLRepo::add_trench_to_repo(const TrenchCoat &t) {
    std::string sql_statement = "INSERT INTO COATS (SIZE, COLOUR, PRICE, QUANTITY, LINK) VALUES (";
    sql_statement += "'" + t.get_trench_size() + "', ";
    sql_statement += "'" + t.get_trench_colour() + "', ";
    sql_statement += "'" + std::to_string(t.get_trench_price()) + "', ";
    sql_statement += "'" + std::to_string(t.get_trench_quantity()) + "', ";
    sql_statement += "'" + t.get_trench_photograph() + "')";
    char* error_message;
    if (sqlite3_exec(this->database, sql_statement.c_str(), nullptr, nullptr, &error_message) != SQLITE_OK) {
        throw RepositoryException("\nError! Cannot add. Trench Coat already in the store.");
    }
}

void SQLRepo::remove_trench_from_repo(TrenchCoat &t) {
    std::string size_copy = t.get_trench_size(), colour_copy = t.get_trench_colour();
    this->find_trench_coat(size_copy, colour_copy);
    std::string sql_statement = "DELETE FROM COATS WHERE SIZE = '" + t.get_trench_size() + "' AND ";
    sql_statement += "COLOUR = '" + t.get_trench_colour() + "';";
    if (sqlite3_exec(this->database, sql_statement.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
        throw RepositoryException("\nError! Cannot remove. Trench Coat not in the store.\n");
    }
}

void SQLRepo::update_trench_in_repo(TrenchCoat &t) {
    std::string sql_statement = "UPDATE COATS SET PRICE = '" + std::to_string(t.get_trench_price()) + "', ";
    sql_statement += "QUANTITY = '" + std::to_string(t.get_trench_quantity()) + "', ";
    sql_statement += "LINK = '" + t.get_trench_photograph() + "' ";
    sql_statement += "WHERE SIZE = '" + t.get_trench_size() + "' AND ";
    sql_statement += "COLOUR = '" + t.get_trench_colour() + "';";
    if (sqlite3_exec(this->database, sql_statement.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
        throw RepositoryException("\nError! Cannot update. The trench coat is not in the store.\n");
    }
}

int SQLRepo::get_repository_size() {
    Records res = select_stmt(this->database, "SELECT * FROM COATS;");
    return res.size();
}

std::vector<TrenchCoat> SQLRepo::get_repository_trenches() {
    std::vector<TrenchCoat> all_coats;
    TrenchCoat t;
    std::string size, colour, link;
    double price;
    int quantity;
    Records res = select_stmt(this->database, "SELECT * FROM COATS;");
    for (auto &record: res) {
        size = record[0];
        colour = record[1];
        price = std::stof(record[2]);
        quantity = std::stoi(record[3]);
        link = record[4];
        t = TrenchCoat{size, colour, price, quantity, link};
        all_coats.push_back(t);
    }
    return all_coats;
}

void SQLRepo::clear_repository() {
    std::string sql_statement = "DELETE FROM COATS";
    if (sqlite3_exec(this->database, sql_statement.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
        throw RepositoryException("\nError! Cannot clear the SQL repository.\n");
    }
}


