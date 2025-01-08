#include <top_conf.hpp>
#include <iostream>

top_conf::top_conf(Gtk::ScrolledWindow& scrolled_window) :
    proc_list_manager{proc_list}    
{
    scrolled_window.set_expand();
    scrolled_window.set_size_request(-1, 450);
    scrolled_window.set_child(proc_list);
}