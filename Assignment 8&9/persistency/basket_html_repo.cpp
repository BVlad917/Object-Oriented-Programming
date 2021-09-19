//
// Created by VladB on 17-Apr-21.
//

#include <regex>
#include <algorithm>
#include <fstream>
#include <cmath>

#include "basket_html_repo.h"
#include "../errors/exceptions.h"

void format_html_line(std::string &line) {
    line = std::regex_replace(line, std::regex("^ +"), "");     // Remove leading spaces (won't remove tabs)
    line = std::regex_replace(line, std::regex("<td>"), "");    // Remove the "<td>" keyword
    line = std::regex_replace(line, std::regex("</td>"), "");   // Remove the "</td>" keyword
    line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());    // Remove possible tabs
}

void BasketHTMLRepo::read_from_file() {
    std::ifstream fin(this->file_name);
    if (!fin.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    this->trench_coats.clear();
    TrenchCoat t;
    std::string aux, size, color, photo;
    int quantity;
    double price;
    // Ignore the first 15 lines of HTML code
    for (int i = 0; i < 14; i++) {
        std::getline(fin, aux);
    }
    while (std::getline(fin, aux)) {
        if (aux == "</table>") break;
        std::getline(fin, aux);     // Read the size
        format_html_line(aux), size = aux;
        std::getline(fin, aux);     // Read the color
        format_html_line(aux), color = aux;
        std::getline(fin, aux);     // Read the price
        format_html_line(aux), price = std::stof(aux);
        std::getline(fin, aux);     // Read the quantity
        format_html_line(aux), quantity = std::stoi(aux);
        std::getline(fin, aux);     // Read the photograph link
        format_html_line(aux);
        // The line with the photograph link needs extra clearing
        aux = std::regex_replace(aux, std::regex("<a href=\""), "");
        aux = std::regex_replace(aux, std::regex("\">Link</a>"), "");
        photo = aux;
        std::getline(fin, aux);     // Ignore the "</tr>" keyword from the end
        t = TrenchCoat{size, color, price, quantity, photo};
        this->trench_coats.push_back(t);
    }
    fin.close();
}

void BasketHTMLRepo::write_to_file() {
    std::ofstream fout(this->file_name);
    if (!fout.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    std::string size, color, price, quantity, photo;
    fout << "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "\t<title>Shopping Basket</title>\n"
            "</head>\n"
            "<body>\n"
            "<table border=\"1\">\n"
            "\t<tr>\n"
            "\t\t<td>Size</td>\n"
            "\t\t<td>Colour</td>\n"
            "\t\t<td>Price</td>\n"
            "\t\t<td>Quantity</td>\n"
            "\t\t<td>Store Link</td>\n"
            "\t</tr>\n";
    for (auto &trench_coat: this->trench_coats) {
        size = trench_coat.get_trench_size();
        color = trench_coat.get_trench_colour();
        double rounded_price = std::ceil(trench_coat.get_trench_price() * 100.0) / 100.0;
        price = std::to_string(rounded_price);
        quantity = std::to_string(trench_coat.get_trench_quantity());
        photo = trench_coat.get_trench_photograph();
        fout << "\t<tr>\n";
        fout << "\t\t<td>" << size << "</td>\n";
        fout << "\t\t<td>" << color << "</td>\n";
        fout << "\t\t<td>" << price.substr(0, price.size() - 4) << "</td>\n";  // Just 2 decimals for the price
        fout << "\t\t<td>" << quantity << "</td>\n";
        fout << "\t\t<td><a href=\"";
        fout << photo << "\">Link</a></td>\n";
        fout << "\t</tr>\n";
    }
    fout << "</table>\n"
            "</body>\n"
            "</html>\n";
}

BasketHTMLRepo::BasketHTMLRepo(std::string &file_name) : BasketFileRepo(file_name) {
    std::ofstream fout(this->file_name);
    if (!fout.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    fout << "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "\t<title>Shopping Basket</title>\n"
            "</head>\n"
            "<body>\n"
            "<table border=\"1\">\n"
            "\t<tr>\n"
            "\t\t<td>Size</td>\n"
            "\t\t<td>Colour</td>\n"
            "\t\t<td>Price</td>\n"
            "\t\t<td>Quantity</td>\n"
            "\t\t<td>Store Link</td>\n"
            "\t</tr>\n"
            "</table>\n"
            "</body>\n"
            "</html>\n";
    fout.close();
}
