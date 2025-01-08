#include <sections_conf.hpp>

sections_conf::sections_conf(Gtk::Box& box) :
    top_manager{top},
    bottom{"bottom"}, bottom_manager{bottom}
{
    box.set_expand();
    box.append(top);
    box.append(bottom);
}