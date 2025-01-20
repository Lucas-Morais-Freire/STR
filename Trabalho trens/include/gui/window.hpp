#ifndef WINDOW_HPP
#define WINDOW_HPP

// 3rd-party
#include <gtkmm/window.h>
#include <gtkmm/box.h>

class window : public Gtk::Window {
    Gtk::Box sections;
public:
    window();
};


#endif