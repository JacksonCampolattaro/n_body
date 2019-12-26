/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <Corrade/Containers/Optional.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/DebugStl.h>
#include <Corrade/Utility/Resource.h>

#include "Magnum/ImageView.h"
#include "Magnum/Platform/GlfwApplication.h"
#include "Magnum/Trade/AbstractImporter.h"
#include "Magnum/Trade/ImageData.h"

namespace Magnum { namespace Platform { namespace Test { namespace {

struct GlfwApplicationTest: Platform::Application {
    explicit GlfwApplicationTest(const Arguments& arguments);

    /* For testing HiDPI resize events */
    void viewportEvent(ViewportEvent& event) override {
        Debug{} << "viewport event" << event.windowSize()
            #ifdef MAGNUM_TARGET_GL
            << event.framebufferSize()
            #endif
            << event.dpiScaling();
    }

    void keyPressEvent(KeyEvent& event) override {
        #if GLFW_VERSION_MAJOR*100 + GLFW_VERSION_MINOR >= 302
        Debug{} << "key press event:" << int(event.key()) << event.keyName();
        #endif

        if(event.key() == KeyEvent::Key::F1) {
            Debug{} << "starting text input";
            startTextInput();
        } else if(event.key() == KeyEvent::Key::Esc) {
            Debug{} << "stopping text input";
            stopTextInput();
        } else if(event.key() == KeyEvent::Key::T) {
            Debug{} << "setting window title";
            setWindowTitle("This is a UTF-8 Window Title™!");
        } else if(event.key() == KeyEvent::Key::S) {
            Debug{} << "setting window size, which should trigger a viewport event";
            setWindowSize(Vector2i{300, 200});
        }
        #if GLFW_VERSION_MAJOR*100 + GLFW_VERSION_MINOR >= 302
        else if(event.key() == KeyEvent::Key::W) {
            Debug{} << "setting max window size, which should trigger a viewport event if the size changes";
            setMaxWindowSize(Vector2i{700, 500});
        }
        #endif
        else if(event.key() == KeyEvent::Key::H) {
            Debug{} << "toggling hand cursor";
            setCursor(cursor() == Cursor::Arrow ? Cursor::Hand : Cursor::Arrow);
        } else if(event.key() == KeyEvent::Key::L) {
            Debug{} << "toggling locked mouse";
            setCursor(cursor() == Cursor::Arrow ? Cursor::HiddenLocked : Cursor::Arrow);
        }
    }

    void mouseMoveEvent(MouseMoveEvent& event) override {
        Debug{} << "mouse move event:" << event.position() << event.relativePosition() << UnsignedInt(event.buttons());
    }

    void textInputEvent(TextInputEvent& event) override {
        Debug{} << "text input event:" << std::string{event.text(), event.text().size()};
    }

    void exitEvent(ExitEvent& event) override {
        Debug{} << "application exiting";
        event.setAccepted(); /* Comment-out to test app exit suppression */
    }

    void drawEvent() override {}
};

GlfwApplicationTest::GlfwApplicationTest(const Arguments& arguments): Platform::Application{arguments, Configuration{}.setWindowFlags(Configuration::WindowFlag::Resizable)} {
    /* For testing resize events */
    Debug{} << "window size" << windowSize()
        #ifdef MAGNUM_TARGET_GL
        << framebufferSize()
        #endif
        << dpiScaling();

    #if GLFW_VERSION_MAJOR*100 + GLFW_VERSION_MINOR >= 302
    Utility::Resource rs{"icons"};
    PluginManager::Manager<Trade::AbstractImporter> manager;
    Containers::Pointer<Trade::AbstractImporter> importer;
    Containers::Optional<Trade::ImageData2D> image16, image32, image64;
    if((importer = manager.loadAndInstantiate("AnyImageImporter")) &&
        importer->openData(rs.getRaw("icon-16.tga")) && (image16 = importer->image2D(0)) &&
        importer->openData(rs.getRaw("icon-32.tga")) && (image32 = importer->image2D(0)) &&
        importer->openData(rs.getRaw("icon-64.tga")) && (image64 = importer->image2D(0))) setWindowIcon({*image16, *image32, *image64});
    else Warning{} << "Can't load the plugin / images, not setting window icon";
    #else
    Debug{} << "GLFW too old, can't set window icon";
    #endif
}

}}}}

MAGNUM_APPLICATION_MAIN(Magnum::Platform::Test::GlfwApplicationTest)