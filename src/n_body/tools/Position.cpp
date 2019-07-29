//
// Created by jackcamp on 6/18/19.
//

#include <cereal/cereal.hpp>
#include "Position.h"

std::string Position::toString() {
    return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ")";
}

template<class Archive>
void Position::serialize(Archive & ar)
{
    ar(
            cereal::make_nvp("x", this->x), cereal::make_nvp("y", this->y), cereal::make_nvp("z", this->z)
    );
}