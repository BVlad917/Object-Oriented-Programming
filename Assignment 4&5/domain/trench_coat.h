//
// Created by VladB on 19-Mar-21.
//

#ifndef A45_BVLAD917_TRENCH_COAT_H
#define A45_BVLAD917_TRENCH_COAT_H

#include <string>

class TrenchCoat {
private:
    std::string size, colour, photograph;
    int quantity{};
    double price{};

public:
    /*
        Default constructor. Size, colour, photograph initialized as empty strings, quantity and price as 0.
     */
    TrenchCoat();

    /*
        Trench coat constructor.
     */
    TrenchCoat(std::string size, std::string colour, double price, int quantity, std::string photograph);

    /*
        Equality operator overloading. Returns true if 2 trench coats have the same size and colour.
     */
    bool operator==(TrenchCoat &other);

    /*
        Inequality operator overloading. Returns true if 2 trench coats have the same size or colour.
     */
    bool operator!=(TrenchCoat &other);

    /*
        Ostream << operator overloading. Used to internally represent the Trench Coat object. Not meant
        to be pretty.
     */
    friend std::ostream &operator<<(std::ostream &out, const TrenchCoat &t);

    /*
        Istream >> operator overloading. Used to read an internally stored Trench Coat object from a file.
     */
    friend std::istream &operator>>(std::istream &in, TrenchCoat &t);

    /*
        Return the trench coat's stock quantity in the store as an integer.
     */
    int get_trench_quantity() const;

    /*
        Return the trench coat's price as a double.
     */
    double get_trench_price() const;

    /*
        Return the trench coat's size as a string.
     */
    std::string get_trench_size();

    /*
        Return the trench coat's colour as a string.
     */
    std::string get_trench_colour();

    /*
        Return the trench coat's photograph as a string.
     */
    std::string get_trench_photograph();
};


#endif //A45_BVLAD917_TRENCH_COAT_H
