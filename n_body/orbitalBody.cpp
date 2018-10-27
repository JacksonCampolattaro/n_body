//
// Created by JackCamp on 8/2/18.
//

#include "orbitalBody.h"
#include "viewport.h"

orbitalBody::orbitalBody(vec3 position, vec3 velocity, float mass, float density, vec3 color, bool fixed) {

    // Setting coordinate values
    this->position = position;
    this->velocity = velocity;

    // Setting volume based on mass and density
    float volume = mass / density;

    // Setting radius based on volume
    radius = pow((volume / float(M_PI)) * (3.0f / 4.0f), (1.0f / 3.0f));

    // Setting properties
    this->mass = mass;
    this->color = color;
    this->fixed = fixed;
}

void orbitalBody::applyVelocity(float interval) {

    this->position += this->velocity * interval;
}

void orbitalBody::applyForce(vec3 force, float interval) {

    if (!fixed) {
        vec3 acceleration = force / mass;

        vec3 velocity = acceleration * interval;

        this->addVelocity(velocity);
    }

}

void orbitalBody::addVelocity(vec3 additionalVelocity) {
    velocity += additionalVelocity;
}

vec3 orbitalBody::getPosition() {
    return position;
}

vec3 orbitalBody::getVelocity() {
    return velocity;
}

float orbitalBody::getMass() {
    return mass;
}

float orbitalBody::getRadius() {
    return radius;
}

vec3 orbitalBody::getColor() {
    return color;
}

void orbitalBody::soundOff() {

    std::cout << "";

    // Prints position, velocity, and mass data in a readable format.
    cout << "[ x Position: " + to_string(position.x) + " | y Position: " + to_string(position.y) +
            " | z Position: " + to_string(position.z) + " ]\n";
    cout << "[ x Velocity: " + to_string(velocity.x) + " | y Velocity: " + to_string(velocity.y) +
            " | z Velocity: " + to_string(velocity.z) + " ]\n";
    cout << "[ Mass: " + to_string(mass) + " ] \n\n";
}

void orbitalBody::draw(viewport *client) {

    viewport::setColor(color);
    viewport::drawCircle(position, radius);
}
