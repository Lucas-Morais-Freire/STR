#include <sections_conf.hpp>

sections_conf::sections_conf(Gtk::Box& box) :
    bottom{Gtk::Orientation::HORIZONTAL},
    top_manager{top},
    bottom_manager{bottom}
{
    box.set_expand();
    box.append(top);
    box.append(bottom);
}