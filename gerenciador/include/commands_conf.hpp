#ifndef COMMANDS_CONF_HPP
#define COMMANDS_CONF_HPP

#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>

class commands_conf {
    Gtk::Box flt_box;
    Gtk::Label flt_lbl;
    Gtk::Entry flt_ent;

    Gtk::Grid pid_grid;
    Gtk::Entry pid_ent;
    Gtk::Label pid_lbl;
    Gtk::Box pid_buts;
    Gtk::Button kill_but, stop_but, cont_but;

    Gtk::Box pri_box;
    Gtk::Entry pri_ent;
    Gtk::Button pri_but;
    
    Gtk::Box cpu_box;
    Gtk::Entry cpu_ent;
    Gtk::Button cpu_but;
public:
    commands_conf(Gtk::Box& box);
    void kill_click();
    void stop_click();
    void cont_click();
    void pri_click();
    void cpu_click();
    void flt_change();
    std::string get_flt_text();
};

#endif