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
    std::string res= "Tuile: ";
    for (auto &it : cases) {
        res += it.second->toString()+" ";
    }
    return res+"\t"+cheminImage;
}