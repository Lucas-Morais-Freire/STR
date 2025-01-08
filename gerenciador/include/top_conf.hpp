#ifndef PROC_LIST_SCROLL_CONF_HPP
#define PROC_LIST_SCROLL_CONF_HPP

// 3rd-party
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>

// my headers
#include <proc_list_conf.hpp>

class top_conf {
    Gtk::TreeView proc_list;
    proc_list_conf proc_list_manager;
public:
    top_conf(Gtk::ScrolledWindow& scrolled_window);
};

#endif