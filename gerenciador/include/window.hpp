#ifndef WINDOW_HPP
#define WINDOW_HPP

// 3rd-party
#include <gtkmm/window.h>
#include <gtkmm/box.h>

// my headers
#include <sections_conf.hpp>

class window : public Gtk::Window {
public:
    window();
protected:
    Gtk::Box sections;
    sections_conf sections_manager;
};

#endif