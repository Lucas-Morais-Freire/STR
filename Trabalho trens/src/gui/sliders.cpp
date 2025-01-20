#include <sliders.hpp>
#include <gtkmm/scale.h>

sliders::sliders(Gtk::Orientation orientation) {
    set_orientation(orientation);
    set_expand();

    Gtk::Scale* vel[4];
    for (int i = 0; i < 4; i++) {
        vel[i] = Gtk::make_managed<Gtk::Scale>(Gtk::Orientation::VERTICAL);
        append(*vel[i]);
        vel[i]->set_expand();
        vel[i]->set_range(0.0, 5.0);
        vel[i]->set_value(0.5);
        vel[i]->set_draw_value();
        vel[i]->set_inverted();
    }
}