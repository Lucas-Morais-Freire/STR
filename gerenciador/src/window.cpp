// std
#include <iostream>

// 3rd-party
#include <glibmm.h>

// my headers
#include <window.hpp>

bool window::on_timeout()
{
    sections_manager.top_manager.proc_list_manager.update_list();
    return true;
}

window::window() :
    sections{Gtk::Orientation::VERTICAL}, sections_manager{sections}
{
    set_default_size(1280, 720);
    set_title("Manager");
    set_child(sections);

    Glib::signal_timeout().connect(sigc::mem_fun(*this, &window::on_timeout), 1000);
}
