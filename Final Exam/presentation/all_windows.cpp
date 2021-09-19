//
// Created by VladB on 22-Jun-21.
//

#include "all_windows.h"
#include "buildings_model.h"

#include <algorithm>
#include <random>

AllWindows::AllWindows(Service &srv): srv{srv} {
    srand(unsigned(time(NULL)));
    std::shuffle(this->colors.begin(), this->colors.end(), std::mt19937(std::random_device()()));

    this->parkModel = new ParkModel{this->srv};
    this->parkWindow = new ParkWindow{this->srv, this->parkModel};

    this->buildingsModel = new BuildingsModel{this->srv};

    int index = 0;
    for (const auto& ethno: this->srv.srvGetAllEthnologists()) {
        this->allWindows.push_back(new EthnologistWindow{this->srv, this->buildingsModel, this->parkModel, ethno.getName(), this->colors[index]});
        index += 1;
    }
}

void AllWindows::showAllWindows() {
    for (auto window: this->allWindows) {
        window->show();
    }
    this->parkWindow->show();
}
