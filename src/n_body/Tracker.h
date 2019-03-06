//
// Created by jackcamp on 2/6/19.
//

#ifndef N_BODY_TRACKER_H
#define N_BODY_TRACKER_H

#include <iostream> // Used for printing outputs to the terminal
#include <ctime> // Used for getting and holding time values

class Tracker {
public:
    static Tracker *instance();

    /**
     * Marks the completion of a new frame of the simulation
     */
    void markFrameCompleted();

    /**
     * Markers for various events in the calculation of the frame
     */
    void markFrameStarted();
    void markTreeCreated();
    void markTreeCompleted();
    void markCenterMassCalculated();
    void markGravityCalculated();
    void markPositionsUpdated();

    /**
     * Outputs information about the most recent frame calculated
     */
    void outputStatus();

private:
    static Tracker *internalInstance; // The Tracker contains one and only one instance of itself

    // This keeps a reference to the model being tracked
    //Simulation *theSim;

    // Data held by the Tracker
    int numFrames;

    clock_t programStartTime;
    clock_t frameStartTime;
    clock_t timeStamp;

    clock_t calculationStartTime;
    clock_t treeCreationTime;
    clock_t treePopulationTime;
    clock_t centerMassCalculationTime;
    clock_t gravityCalculationTime;
    clock_t positionUpdateTime;
    clock_t totalCalculationTime;
    clock_t renderingTime;
    clock_t totalFrameTime;

    // TODO these are temporary
    clock_t a;
    clock_t b;

    Tracker(Tracker const &) = default; // The copy constructor is private
    //Tracker &operator=(Tracker const &) {}; // The assignment operator is private
    Tracker() = default; // Only the Tracker is allowed to construct itself

    /**
     * Converts clock time to seconds
     * @param cycles Elapsed time in cpu clock cycles
     * @return Elapsed time in seconds
     */
    double inSeconds(clock_t cycles) {
        return cycles / (double) CLOCKS_PER_SEC;
    }
};


#endif //N_BODY_TRACKER_H