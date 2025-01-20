#include <train_panel.hpp>
#include <iostream>

train_panel::train_panel() {
    set_expand();
    set_draw_func(sigc::mem_fun(*this, &train_panel::on_draw));
    queue_draw();

    // signal_resize().connect([this](int, int){ queue_draw(); });
}

void train_panel::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    cr->set_source_rgba(0.8, 0.8, 0.8, 1);
    cr->rectangle(0, 0, width, height);
    cr->fill();

    const double rec_sz = height/2.0;
    cr->set_source_rgba(0.3, 0.3, 0.3, 1);
    cr->set_line_width(5);

    cr->rectangle(width/2.0 - 1.5*rec_sz + 10, 0.75*height - 0.5*rec_sz + 10, 3*rec_sz - 20, rec_sz - 20);
    cr->stroke();
    cr->rectangle(width/2.0 - 0.5*rec_sz + 10, 0.25*height - 0.5*rec_sz + 10, rec_sz - 20, rec_sz - 20);
    cr->stroke();
    cr->rectangle(width/2.0 - 1.5*rec_sz + 10, 0.25*height - 0.5*rec_sz + 10, rec_sz - 20, rec_sz - 20);
    cr->stroke();
    cr->rectangle(width/2.0 + 0.5*rec_sz + 10, 0.25*height - 0.5*rec_sz + 10, rec_sz - 20, rec_sz - 20);
    cr->stroke();
}