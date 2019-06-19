//
// Created by jackcamp on 6/18/19.
//

#ifndef N_BODY_POSITION_H
#define N_BODY_POSITION_H


#include <glm/vec3.hpp>

class Position : public glm::vec3 {

public:

    Position(float x, float y, float z) : glm::vec3(x, y, z){};

    std::string toString();

    template<class Archive>
    void serialize(Archive & ar);
};


#endif //N_BODY_POSITION_H