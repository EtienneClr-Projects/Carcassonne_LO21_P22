//
// Created by etienne on 27/04/2022.
//

#include "Tuile.h"

#include <utility>

Tuile::Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage) {
    this->cases = std::move(cases);
    this->cheminImage = std::move(cheminImage);
}

std::string Tuile::toString() {
    std::string res = "Tuile:\n";
    int i = 1;
    for (auto &it: cases) {
        res += it.second->toString() + " ";
        if (i % 3 == 0) res += "\n";
        i++;
    }
    return res + "\t" + cheminImage;
}