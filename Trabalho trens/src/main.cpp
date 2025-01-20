// 3rd-party
#include <gtkmm/application.h>

// my headers
#include <window.hpp>

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<window>(argc, argv);
}