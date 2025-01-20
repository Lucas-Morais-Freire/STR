#ifndef TRAIN_PANEL_HPP
#define TRAIN_PANEL_HPP

#include <gtkmm/drawingarea.h>

class train_panel : public Gtk::DrawingArea {
public:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    train_panel();
};

#endif