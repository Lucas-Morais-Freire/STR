#ifndef TRAIN_PANEL_HPP
#define TRAIN_PANEL_HPP

// 3rd-party
#include <gtkmm/drawingarea.h>

// my headers
#include <trains.hpp>

class train_panel : public Gtk::DrawingArea {
    trains* instance;
    void draw_train0(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void draw_train1(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void draw_train2(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void draw_train3(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    bool timeout_callback();
public:
    train_panel(useconds_t refresh_rate);
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
};

#endif