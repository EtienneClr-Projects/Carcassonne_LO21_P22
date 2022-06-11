#include "CasesTuilesEtZones/Case.h"


Case::Case(ZONE_TYPE zt, DIRECTION d, SUPP_TYPE s, int i) : zone_type(zt), direction(d), supp_type(s), id_connexion(i),
                                                            tuile_parente(nullptr), zone_parente(nullptr),
                                                            meeple_pose(nullptr) {}

std::string Case::toString() {
    std::string res;
    res += ParametresPartie::toStringZONE_TYPE(zone_type);
    if (meeple_pose != nullptr)
        res += "m";//on signale la présence d'un meeple par un petit m
//    else
//        res += ParametresPartie::toStringSUPP_TYPE(supp_type);
    else if (zone_parente != nullptr && zone_parente->getType() != ZONE_TYPE::PRAIRIE)
        res += std::to_string(zone_parente->ouvertures);
    else if (supp_type != SUPP_TYPE::AUCUN)
        res += ParametresPartie::toStringSUPP_TYPE(supp_type)[0];
    else
        res += " ";
    return res;
}

void Case::setZoneParente(Zone *z) { zone_parente = z; }

void Case::setDirection(DIRECTION c) { direction = c; }

void Case::setMeeple(Meeple *m) { meeple_pose = m; }

int Case::getIdConnexion() const { return id_connexion; }

ZONE_TYPE Case::getZoneType() const { return zone_type; }

DIRECTION Case::getDirection() const { return direction; }

SUPP_TYPE Case::getSuppType() const { return supp_type; }

Tuile *Case::getTuileParente() const { return tuile_parente; }

Zone *Case::getZoneParente() const { return zone_parente; }

Meeple *Case::getMeeplePose() const { return meeple_pose; }

void Case::setTuileParente(Tuile *t) { tuile_parente = t; }

void Case::retirerMeeplePose() { meeple_pose = nullptr; }
