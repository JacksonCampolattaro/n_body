//
// Created by jackcamp on 1/26/20.
//

#ifndef N_BODY_APPLICATION_H
#define N_BODY_APPLICATION_H

#include "Logger.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <iostream>

namespace Controller {

    /**
     * @brief An extension of Gtkmm's application class with project-specific features.
     *
     * This extension of Gtk::Application makes instancing my project easier.
     * It parses extra command line instructions and uses them to determine which features to enable.
     */
    class Application : public Gtk::Application {
    public:

        static Glib::RefPtr<Application> create();

    protected:

        /**
         * @brief The default constructor defines a number of CLI options.
         *
         * This constructor sets the application's name and
         * provides descriptions for the program's various CLI options.
         */
        Application();

        int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine> &command_line) override;

        void on_startup() override;

        void on_activate() override;

    private:

        Gtk::Window _window;
    };

}


#endif //N_BODY_APPLICATION_H