#include <bottom_conf.hpp>

bottom_conf::bottom_conf(Gtk::Box& box) :
    commands{Gtk::Orientation::VERTICAL},
    cpu{"Uso da CPU"},
    commands_manager{commands},
    cpu_manager{cpu}
{
    box.set_expand();
    box.append(commands);
    box.append(cpu);
}