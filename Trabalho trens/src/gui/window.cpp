// 3rd-party
#include <gtkmm/frame.h>

// my headers
#include <window.hpp>
#include <train_panel.hpp>
#include <sliders.hpp>

window::window() :
    sections(Gtk::Orientation::VERTICAL)
{
    set_default_size(1280, 720);
    set_title("Trens");
    set_child(sections);

    train_panel* trains = Gtk::make_managed<train_panel>(17000);
    sliders* velocities = Gtk::make_managed<sliders>(Gtk::Orientation::HORIZONTAL);

    sections.set_expand();
    sections.append(*trains);
    sections.append(*velocities);
}