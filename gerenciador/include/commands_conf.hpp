#ifndef COMMANDS_CONF_HPP
#define COMMANDS_CONF_HPP

#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>

class commands_conf {
    Gtk::Grid pid_grid;
    Gtk::Entry pid_ent;
    Gtk::Label pid_lbl;
    Gtk::Box pid_buts;
    Gtk::Button kill, stop, cont;

    Gtk::Box pri_box;
    Gtk::Entry pri_ent;
    Gtk::Button pri_but;
    
    Gtk::Box cpu_box;
    Gtk::Entry cpu_ent;
    Gtk::Button cpu_but;
public:
    commands_conf(Gtk::Box& box);
};

#endif