//
// Created by jackcamp on 10/25/18.
//

#include <gtest/gtest.h>
#include <omp.h>

#include "body.h"
#include "simulation.h"
#include "viewport.h"


float density = 100;

simulation *theSimulation;
viewport *theViewport;

// Colors to use
static vec3 white = vec3(1, 1, 1);
static vec3 yellow = vec3(1, 1, 0);
static vec3 red = vec3(1, 0, 0);
static vec3 green = vec3(0, 1, 0);
static vec3 blue = vec3(0, 0, 1);
static vec3 teal = vec3(0, 1, 1);
static vec3 grey = vec3(.5, .5, .5);


void addBody(body *newBody) {
    theSimulation->addBody(newBody);
    theViewport->registerDrawable(newBody);
}


void cubicGrid(vec3 cornerPosition = vec3(-100, -100, -200), vec3 velocity = vec3(0.0f, 0.0f, -100.0f),
               vec3 size = vec3(20, 20, 20), float spacing = 10.0f, float mass = 10000.0f) {

    theSimulation->setPower(2);

    // Creates a cubic grid

    for (int x = 0; x < size.x; ++x) {
        for (int y = 0; y < size.y; ++y) {
            for (int z = 0; z < size.z; ++z) {

                vec3 coordinate(x, y, z);
                vec3 position = cornerPosition + (coordinate * spacing);

                if (x < 0) {
                    velocity *= -1;
                }

                vec3 multiColor = coordinate / size + 0.2f;
                vec3 yellowToRed(1, coordinate.y / size.y, 0);
                vec3 greenToWhite(coordinate.y / size.y, 1, coordinate.y / size.y);
                vec3 blueToRed(coordinate.y / size.y, 0, 1 - coordinate.y / size.y);
                vec3 blueToRedToWhite(coordinate.y / size.y + coordinate.x / size.x, coordinate.x / size.x,
                                      1 - coordinate.y / size.y + coordinate.x / size.x);
                vec3 rainbow(coordinate.y / size.y, coordinate.x / size.x, 1 - coordinate.y / size.y);


                auto newBody = new body(position, velocity, mass, density, blueToRedToWhite, false);
                addBody(newBody);
            }
        }
    }
}


void bigDemo() {

    // Massive fixed mass
    auto superHeavy = new body(vec3(0, 0, -500), vec3(0, 0, 0), 180000000, 1000, white, true);
    addBody(superHeavy);

    // Cubic Grid
    vec3 cornerPosition(-50, -100, -450);
    vec3 velocity(30.0f, 15.0f, 0.0f);
    vec3 size(4, 4, 150);
    float spacing = 10.0f;
    float mass = 10000.0f;

    for (int x = 0; x < size.x; ++x) {
        for (int y = 0; y < size.y; ++y) {
            for (int z = 0; z < size.z; ++z) {

                vec3 coordinate(x, y, z);
                vec3 position = cornerPosition + (coordinate * spacing);

                if (x < 0) {
                    velocity *= -1;
                }

                vec3 multiColor = coordinate / size + 0.2f;
                vec3 yellowToRed(1, coordinate.y / size.y, 0);
                vec3 yellowToRed_Z(1, coordinate.z / size.z, 0);
                vec3 greenToWhite(coordinate.y / size.y, 1, coordinate.y / size.y);
                vec3 blueToRed(coordinate.y / size.y, 0, 1 - coordinate.y / size.y);
                vec3 blueToRed_Z(coordinate.z / size.z, 0, 1 - coordinate.z / size.z);
                vec3 blueToRedToWhite(coordinate.y / size.y + coordinate.x / size.x, coordinate.x / size.x,
                                      1 - coordinate.y / size.y + coordinate.x / size.x);
                vec3 whiteToBlueToRed(coordinate.y / size.y + coordinate.z / size.z, coordinate.z / size.z,
                                      1 - coordinate.y / size.y + coordinate.z / size.z);
                vec3 rainbow(coordinate.y / size.y, coordinate.x / size.x, 1 - coordinate.y / size.y);


                auto newBody = new body(position, velocity, mass, density, yellowToRed, false);
                theSimulation->orbit(superHeavy, newBody);
                addBody(newBody);
            }
        }
    }
}


void threeBodyDemo() {
    // Three body simulation

    theSimulation->setPower(1);
    theSimulation->setGravitationalConstant(1);
    theSimulation->setTimeInterval(.001);
    addBody(new body(vec3(20.0, 50.0, -300), vec3(30, -50, 0), 500000, density, red));
    addBody(new body(vec3(0.0, -50, -400), vec3(-30, 0, 0), 500000, density, white));
    addBody(new body(vec3(-20, 0, -700), vec3(0, 50, 0), 500000, density, yellow));
}


void addBodies() {

    // Orbit simulation
    /*
    auto sun = new body(vec3(0, 0, -4000), vec3(0, 0, 0), 50000000, density, yellow, true);
    addBody(sun);

    auto earth = new body(vec3(2000, 0, -4000), vec3(0, 1, 0), 4000000, density, blue);
    addBody(earth);
    theSimulation->orbit(sun, earth);

    auto moon = new body(vec3(2000, -130, -4000), vec3(0, 0, 1), 500, .1, white);
    theSimulation->orbit(earth, moon);
    moon->addVelocity(earth->getVelocity());
    addBody(moon);
    //*/

    bigDemo();
    //cubicGrid(vec3(-95, -95, -200), vec3(0, 0, -50), vec3(20, 20, 20));
    //threeBodyDemo();

    //cubicGrid(vec3(-50, -50, -500), vec3(100, 0, 0), vec3(10, 10, 10));
    //cubicGrid(vec3(-50, 50, -500), vec3(-100, 0, 0), vec3(10, 10, 10));
}

int main(int argc, char **argv) {

    cout << " number of devices: " << omp_get_num_devices() << endl;

    // Creating simulation
    theSimulation = new simulation(.05, .005, 2);

    // Starting GLFW
    theViewport = new viewport(theSimulation, 2000, 1000);

    // Adding bodies
    addBodies();

    // Starting the simulation
    theViewport->graphicsLoop();

}