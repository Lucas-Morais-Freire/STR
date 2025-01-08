// std
#include <iostream>
#include <signal.h>
#include <sys/resource.h>

// my headers
#include <utils.hpp>
#include <commands_conf.hpp>
#include <window.hpp>

commands_conf::commands_conf(Gtk::Box &box) :
    flt_box{Gtk::Orientation::HORIZONTAL},
    flt_lbl{"Filtrar"},

    pid_lbl{"PID do processo"},
    pid_buts{Gtk::Orientation::VERTICAL},
    kill_but{"kill"},
    stop_but{"stop"},
    cont_but{"cont"},
    
    pri_box{Gtk::Orientation::HORIZONTAL},
    pri_but{"Prioridade"},

    cpu_box{Gtk::Orientation::HORIZONTAL},
    cpu_but{"CPU"}
{
    box.set_expand();
    box.set_spacing(50);
    box.append(flt_box);
    box.append(pid_grid);
    box.append(pri_box);
    box.append(cpu_box);

    flt_box.set_expand();
    flt_box.append(flt_lbl); {
        flt_lbl.set_expand();
    }
    flt_box.append(flt_ent); {
        flt_ent.set_hexpand();
        flt_ent.signal_changed().connect(sigc::mem_fun(*this, &commands_conf::flt_change));
    }

    pid_grid.set_expand();
    pid_grid.attach(pid_lbl, 0, 1); {
        // pid_lbl.set_expand();
        pid_lbl.set_margin(10);
    }
    pid_grid.attach(pid_ent, 1, 1, 1, 1); {
        pid_ent.set_hexpand(true);
    }
    pid_grid.attach(pid_buts, 2, 0, 1, 3); {
        pid_buts.set_expand();
    }
    pid_buts.append(kill_but); {
        kill_but.set_expand();
        kill_but.signal_clicked().connect(sigc::mem_fun(*this, &commands_conf::kill_click));
    }
    pid_buts.append(stop_but); {
        stop_but.set_expand();
        stop_but.signal_clicked().connect(sigc::mem_fun(*this, &commands_conf::stop_click));
    }
    pid_buts.append(cont_but); {
        cont_but.set_expand();
        cont_but.signal_clicked().connect(sigc::mem_fun(*this, &commands_conf::cont_click));
    }

    pri_box.set_expand();
    pri_box.append(pri_but); {
        pri_but.set_expand();
        pri_but.signal_clicked().connect(sigc::mem_fun(*this, &commands_conf::pri_click));
    }
    pri_box.append(pri_ent); {
        pri_ent.set_expand();
    }

    cpu_box.set_expand();
    cpu_box.append(cpu_but); {
        cpu_but.set_expand();
    }
    cpu_box.append(cpu_ent); {
        cpu_ent.set_expand();
    }
}

void commands_conf::kill_click()
{
    std::string text = pid_ent.get_text();
    if (!utils::is_uint(text)) {
        std::cout << text << " is not a valid PID number!\n";
        return;
    }
    kill(std::stoul(pid_ent.get_text()), SIGKILL);
}

void commands_conf::stop_click()
{
    std::string text = pid_ent.get_text();
    if (!utils::is_uint(text)) {
        std::cout << text << " is not a valid PID number!\n";
        return;
    }
    kill(std::stoul(pid_ent.get_text()), SIGSTOP);
}

void commands_conf::cont_click()
{
    std::string text = pid_ent.get_text();
    if (!utils::is_uint(text)) {
        std::cout << text << " is not a valid PID number!\n";
        return;
    }
    kill(std::stoul(pid_ent.get_text()), SIGCONT);
}

void commands_conf::pri_click() {
    std::string text = pid_ent.get_text();
    if (text.size() == 0) {
        return;
    }
    if (!utils::is_uint(text)) {
        std::cout << text << " is not a valid PID number!\n";
        return;
    }

    std::string p_text = pri_ent.get_text();
    if (p_text.size() == 0) {
        return;
    }
    if (p_text[0] > '9' || (!(p_text[0] == '-') && p_text[0] < '0')) {
        std::cout << p_text << " is not a valid priority number! (-20 <= PRI <= 19)\n";
        return;
    }
    for (size_t i = 1; i < p_text.size(); i++) {
        if (p_text[i] < '0' || p_text[i] > '9') {
            std::cout << p_text << " is not a valid priority number! (-20 <= PRI <= 19)\n";
            return;
        }
    }

    std::cout << std::stoul(text) << std::stoi(p_text) << '\n';
    setpriority(PRIO_PROCESS, std::stoul(text), std::stoi(p_text));
}

void commands_conf::flt_change()
{
    window* w = static_cast<window*>(flt_box.get_parent()->get_parent()->get_parent()->get_parent());
    w->sections_manager.top_manager.proc_list_manager.update_list();
}

std::string commands_conf::get_flt_text()
{
    return flt_ent.get_text();
}

