//
// Created by jackcamp on 5/24/19.
//

#include "nbody_window.h"
#include "../Launcher/Preset.h"
#include "../model/calculation/BarnesHut/BarnesHutSolver.h"
#include "../Controller.h"

nbody_window::nbody_window() {

    add(mainBox);

    notebook.set_can_focus(false);
    notebook.append_page(physicsPage, "Physics");
    notebook.append_page(viewPage, "View");
    viewPage.pack_start(recorderCreator, Gtk::PACK_SHRINK);

    mainBox.pack_start(notebook);


    run_button.set_halign(Gtk::ALIGN_END);
    run_button.signal_clicked().connect(sigc::mem_fun(*this, &nbody_window::on_run_clicked));
    actionBar.pack_end(run_button);
    actionBar.set_size_request(200, 40);
    mainBox.pack_start(actionBar, Gtk::PACK_SHRINK);

    show_all_children();
}

void nbody_window::on_run_clicked() {

    // Creating the default physics context
    auto physicsContext = new PhysicsContext();
    ///physicsContext->setT(0.01)->setG(0.02)->setPower(2);

    // Loading a world from my collection of presets
    Preset myPreset = Preset();
    myPreset.blender();
    physicsContext = myPreset.getPhysicsContext();
    auto bodies = myPreset.getBodies();

    physicsContext = physicsPage.createPhysicsContext();

    // Configuring the solving tool
    auto *solver = new BarnesHutSolver();
    solver->enableThreading();
    solver->setTheta(0.8);

    // Creating the model
    auto model = new Model(physicsContext, solver);

    // Creating the view
    auto view = viewPage.createView();


    // Creating the recorder
    auto recorder = recorderCreator.createRecorder(view);

    // Launching the program
    auto controller = Controller(model, view, bodies, recorder);
    controller.run();
}
