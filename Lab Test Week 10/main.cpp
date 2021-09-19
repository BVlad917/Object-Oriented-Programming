//
// Created by VladB on 26-Apr-21.
//

#include <iostream>
#include "persistency/person.h"
#include "business/service.h"
#include "presentation/ui.h"

int main() {
    Person p{"Vlad Bogdan"};
    Service srv{p};
    UI ui{srv};
    ui.start();
    return 0;
}