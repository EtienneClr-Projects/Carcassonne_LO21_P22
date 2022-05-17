//
// Created by etienne on 10/05/2022.
//

#ifndef CARCASSONNE_LO21_P22_COORD_H
#define CARCASSONNE_LO21_P22_COORD_H


#include <string>

class Coord {
    int x_;
    int y_;

public:
    Coord(int x, int y) {
        this->x_ = x;
        this->y_ = y;
    }

    int x() const {
        return x_;
    }

    int y() const {
        return y_;
    }

    std::string toString() const {
        return "("+std::to_string(x_) + "," + std::to_string(y_)+")";
    };

    bool operator==(const Coord &c) const {
        return (this->x_ == c.x_ && this->y_ == c.y_);
    }

    Coord operator+(const Coord &c) const {
        return {this->x_ + c.x_, this->y_ + c.y_};
    }

};


#endif //CARCASSONNE_LO21_P22_COORD_H
