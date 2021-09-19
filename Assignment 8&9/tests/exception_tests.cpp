//
// Created by VladB on 21-Mar-21.
//

#include <cassert>
#include "exception_tests.h"
#include "../errors/exceptions.h"

void ExceptionTests::test_exception_messages() {
    try {
        throw DynamicArrayException("Bad dynamic array.");
    }
    catch (DynamicArrayException &de) {
        std::string expected = "Bad dynamic array.";
        assert(de.what() == expected);
    }
    try {
        throw RepositoryException("Bad repo.");
    }
    catch (RepositoryException &re) {
        std::string expected = "Bad repo.";
        assert(re.what() == expected);
    }
    try {
        throw ValidationException("Bad validation.");
    }
    catch (ValidationException &ve) {
        std::string expected = "Bad validation.";
        assert(ve.what() == expected);
    }
    try {
        throw ServiceException("Bad service.");
    }
    catch (ServiceException &se) {
        std::string expected = "Bad service.";
        assert(se.what() == expected);
    }
}

void ExceptionTests::run_all_exception_tests() {
    test_exception_messages();
}
