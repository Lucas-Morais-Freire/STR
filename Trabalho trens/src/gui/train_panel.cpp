// std
#include <iostream>

// 3rd-party
#include <glibmm.h>

// my headers
#include <train_panel.hpp>

#define RADIUS 10

train_panel::train_panel(useconds_t refresh_rate) {
    instance = trains::get_instance(refresh_rate);

    set_expand();
    set_draw_func(sigc::mem_fun(*this, &train_panel::on_draw));
    queue_draw();

    Glib::signal_timeout().connect(sigc::mem_fun(*this, &train_panel::timeout_callback), refresh_rate/1000);
}

void train_panel::draw_train0(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    const double rec_sz = height/2.0;
    double progress = instance->get_progress(0);

    cr->set_source_rgb(1, 0, 0);
    if (0.0 <= progress && progress < 1.0) {
        cr->arc(width/2.0 - 1.5*rec_sz + 10,  0.75*height + 0.5*rec_sz - 10 - progress*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    } else if (1.0 <= progress && progress < 4.0) {
        cr->arc(width/2.0 - 1.5*rec_sz + 10 + (progress - 1.0)*(rec_sz - 20/3.0),  0.75*height - 0.5*rec_sz + 10, RADIUS, 0, 2*M_PI);
    } else if (4.0 <= progress && progress < 5.0) {
        cr->arc(width/2.0 + 1.5*rec_sz - 10, 0.75*height - 0.5*rec_sz + 10 + (progress - 4.0)*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    } else if (5.0 <= progress && progress <= 8.0) {
        cr->arc(width/2.0 + 1.5*rec_sz - 10 - (progress - 5.0)*(rec_sz - 20/3.0), 0.75*height + 0.5*rec_sz - 10, RADIUS, 0, 2*M_PI);
    }
    cr->fill();
}

void train_panel::draw_train1(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    const double rec_sz = height/2.0;
    double progress = instance->get_progress(1);

    cr->set_source_rgb(0, 1, 0);
    if (0.0 <= progress && progress < 1.0) {
        cr->arc(width/2.0 - 1.5*rec_sz + 10 + progress*(rec_sz - 20), 0.25*height - 0.5*rec_sz + 10, RADIUS, 0, 2*M_PI);
    } else if (1.0 <= progress && progress < 2.0) {
        cr->arc(width/2.0 - 0.5*rec_sz - 10, 0.25*height - 0.5*rec_sz + 10 + (progress - 1.0)*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    } else if (2.0 <= progress && progress < 3.0) {
        cr->arc(width/2.0 - 0.5*rec_sz - 10 - (progress - 2.0)*(rec_sz - 20), 0.25*height + 0.5*rec_sz - 10, RADIUS, 0, 2*M_PI);
    } else if (3.0 <= progress && progress < 4.0) {
        cr->arc(width/2.0 - 1.5*rec_sz + 10, 0.25*height + 0.5*rec_sz - 10 - (progress - 3.0)*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    }
    cr->fill();
}

void train_panel::draw_train2(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    const double rec_sz = height/2.0;
    double progress = instance->get_progress(2);

    cr->set_source_rgb(0, 0, 1);
    if (0.0 <= progress && progress < 1.0) {
        cr->arc(width/2.0 - 0.5*rec_sz + 10 + progress*(rec_sz - 20), 0.25*height - 0.5*rec_sz + 10, RADIUS, 0, 2*M_PI);
    } else if (1.0 <= progress && progress < 2.0) {
        cr->arc(width/2.0 + 0.5*rec_sz - 10, 0.25*height - 0.5*rec_sz + 10 + (progress - 1.0)*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    } else if (2.0 <= progress && progress < 3.0) {
        cr->arc(width/2.0 + 0.5*rec_sz - 10 - (progress - 2.0)*(rec_sz - 20), 0.25*height + 0.5*rec_sz - 10, RADIUS, 0, 2*M_PI);
    } else if (3.0 <= progress && progress < 4.0) {
        cr->arc(width/2.0 - 0.5*rec_sz + 10, 0.25*height + 0.5*rec_sz - 10 - (progress - 3.0)*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    }
    cr->fill();
}

void train_panel::draw_train3(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    const double rec_sz = height/2.0;
    double progress = instance->get_progress(3);

    cr->set_source_rgb(0, 1, 1);
    if (0.0 <= progress && progress < 1.0) {
        cr->arc(width/2.0 + 0.5*rec_sz + 10 + progress*(rec_sz - 20), 0.25*height - 0.5*rec_sz + 10, RADIUS, 0, 2*M_PI);
    } else if (1.0 <= progress && progress < 2.0) {
        cr->arc(width/2.0 + 1.5*rec_sz - 10, 0.25*height - 0.5*rec_sz + 10 + (progress - 1.0)*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    } else if (2.0 <= progress && progress < 3.0) {
        cr->arc(width/2.0 + 1.5*rec_sz - 10 - (progress - 2.0)*(rec_sz - 20),  0.25*height + 0.5*rec_sz - 10, RADIUS, 0, 2*M_PI);
    } else if (3.0 <= progress && progress < 4.0) {
        cr->arc(width/2.0 + 0.5*rec_sz + 10, 0.25*height + 0.5*rec_sz - 10 - (progress - 3.0)*(rec_sz - 20), RADIUS, 0, 2*M_PI);
    }
    cr->fill();
}

bool train_panel::timeout_callback() {
    queue_draw();
    return true;
}

void train_panel::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    // draw background
    cr->set_source_rgba(0.8, 0.8, 0.8, 1);
    cr->rectangle(0, 0, width, height);
    cr->fill();

    // draw rails
    const double rec_sz = height/2.0;
    cr->set_source_rgba(0.3, 0.3, 0.3, 1);
    cr->set_line_width(5);

    cr->rectangle(width/2.0 - 1.5*rec_sz + 10, 0.75*height - 0.5*rec_sz + 10, 3*rec_sz - 20, rec_sz - 20);
    cr->stroke();
    cr->rectangle(width/2.0 - 1.5*rec_sz + 10, 0.25*height - 0.5*rec_sz + 10, rec_sz - 20, rec_sz - 20);
    cr->stroke();
    cr->rectangle(width/2.0 - 0.5*rec_sz + 10, 0.25*height - 0.5*rec_sz + 10, rec_sz - 20, rec_sz - 20);
    cr->stroke();
    cr->rectangle(width/2.0 + 0.5*rec_sz + 10, 0.25*height - 0.5*rec_sz + 10, rec_sz - 20, rec_sz - 20);
    cr->stroke();

    // draw trains
    draw_train0(cr, width, height);
    draw_train1(cr, width, height);
    draw_train2(cr, width, height);
    draw_train3(cr, width, height);
}