#ifndef WINDOW_HPP
#define WINDOW_HPP

// 3rd-party
#include <gtkmm/window.h>
#include <gtkmm/box.h>

// my headers
#include <sections_conf.hpp>

class window : public Gtk::Window {
    Gtk::Box sections;

    bool on_timeout();
public:
    sections_conf sections_manager;
    window();
};

#endif