// std
#include <iostream>

// 3rd-party
#include <gtkmm/treeview.h>
#include <gtkmm/frame.h>
#include <gtkmm/liststore.h>

// my headers
#include <window.hpp>

window::window() : sections{Gtk::Orientation::VERTICAL}, sections_manager{sections} {
    set_default_size(1280, 720);
    set_title("Manager");
    set_child(sections);
}