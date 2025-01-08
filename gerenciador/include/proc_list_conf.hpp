#ifndef PROC_LIST_CONF_HPP
#define PROC_LIST_CONF_HPP

#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>

class proc_list_conf {
    Glib::RefPtr<Gtk::ListStore> list_store;

    class proccols : public Gtk::TreeModel::ColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<float> usage;
        Gtk::TreeModelColumn<pid_t> pid;
        Gtk::TreeModelColumn<pid_t> ppid;
        Gtk::TreeModelColumn<int> pri;
        Gtk::TreeModelColumn<Glib::ustring> status;

        proccols() { add(name); add(usage); add(pid); add(ppid); add(pri); add(status); }
    } columns;
public:
    proc_list_conf(Gtk::TreeView& proc_list);
};

#endif