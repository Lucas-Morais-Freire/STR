#include <commands_conf.hpp>

commands_conf::commands_conf(Gtk::Box &box) :
    pid_lbl{"PID do processo"},
    pid_buts{Gtk::Orientation::VERTICAL},
    kill{"kill"},
    stop{"stop"},
    cont{"cont"},
    
    pri_box{Gtk::Orientation::HORIZONTAL},
    pri_but{"Prioridade"},

    cpu_box{Gtk::Orientation::HORIZONTAL},
    cpu_but{"CPU"}
{
    box.set_expand();
    box.set_spacing(50);
    box.append(pid_grid);
    box.append(pri_box);
    box.append(cpu_box);

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
    pid_buts.append(kill); {
        kill.set_expand();
    }
    pid_buts.append(stop); {
        stop.set_expand();
    }
    pid_buts.append(cont); {
        cont.set_expand();
    }

    pri_box.set_expand();
    pri_box.append(pri_but); {
        pri_but.set_expand();
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