#ifndef BOTTOM_CONF_HPP
#define BOTTOM_CONF_HPP

#include <gtkmm/box.h>
#include <gtkmm/frame.h>

// my headers
#include <commands_conf.hpp>
#include <cpu_conf.hpp>

class bottom_conf {
    Gtk::Box commands;
    Gtk::Frame cpu;
public:
    commands_conf commands_manager;
    cpu_conf cpu_manager;
    bottom_conf(Gtk::Box& box);
};

#endif