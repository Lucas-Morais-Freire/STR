// 3rd-party
#include <gtkmm/application.h>

// my headers
#include <window.hpp>
#include <trains.hpp>

void* train0(void*) {
    trains* instance = trains::get_instance();

    instance->train0();

    return nullptr;
}

void* train1(void*) {
    trains* instance = trains::get_instance();

    instance->train1();

    return nullptr;
}

void* train2(void*) {
    trains* instance = trains::get_instance();

    instance->train2();

    return nullptr;
}

void* train3(void*) {
    trains* instance = trains::get_instance();

    instance->train3();

    return nullptr;
}

int main(int argc, char** argv) {
    pthread_t train0_t;
    pthread_create(&train0_t, nullptr, train0, nullptr);
    pthread_t train1_t;
    pthread_create(&train1_t, nullptr, train1, nullptr);
    pthread_t train2_t;
    pthread_create(&train2_t, nullptr, train2, nullptr);
    pthread_t train3_t;
    pthread_create(&train3_t, nullptr, train3, nullptr);

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<window>(argc, argv);
}