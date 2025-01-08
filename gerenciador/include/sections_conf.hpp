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
    top_conf top_manager;

    Gtk::Frame bottom;
    bottom_conf bottom_manager;
public:
    sections_conf(Gtk::Box& box);
};

#endif