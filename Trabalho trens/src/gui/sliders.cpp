// 3rd-party
#include <gtkmm/scale.h>

// my headers
#include <sliders.hpp>
#include <trains.hpp>

sliders::sliders(Gtk::Orientation orientation) {
    set_orientation(orientation);
    set_expand();
    trains* instance = trains::get_instance();

    Gtk::Scale* vel[4];
    for (int i = 0; i < 4; i++) {
        vel[i] = Gtk::make_managed<Gtk::Scale>(Gtk::Orientation::VERTICAL);
        append(*vel[i]);
        vel[i]->set_expand();
        vel[i]->set_range(0.0, 5.0);
        vel[i]->set_value(0.5);
        vel[i]->set_draw_value();
        vel[i]->set_inverted();
        vel[i]->signal_value_changed().connect([vel, i, instance](){
            instance->set_velocity(i, vel[i]->get_value());
        });
        vel[i]->add_mark(0, Gtk::PositionType::BOTTOM, std::string("Trem ") + std::to_string(i));
    }
}