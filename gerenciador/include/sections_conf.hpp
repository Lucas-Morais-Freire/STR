#ifndef SECTIONS_CONF_HPP
#define SECTIONS_CONF_HPP

// 3rd-party
#include <gtkmm/box.h>
#include <gtkmm/frame.h>

// my headers
#include <top_conf.hpp>
#include <bottom_conf.hpp>

class sections_conf {
    Gtk::ScrolledWindow top;
    Gtk::Box bottom;
    
public:
    top_conf top_manager;
    bottom_conf bottom_manager;
    sections_conf(Gtk::Box& box);
};

#endif