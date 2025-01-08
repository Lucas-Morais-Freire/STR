#ifndef PROC_LIST_CONF_HPP
#define PROC_LIST_CONF_HPP

// 3rd-party
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>

class proc_list_conf {
    Glib::RefPtr<Gtk::ListStore> list_store;
    Gtk::TreeView& proc_list;

    class proccols : public Gtk::TreeModel::ColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> cmd;
        Gtk::TreeModelColumn<double> usage;
        Gtk::TreeModelColumn<pid_t> pid;
        Gtk::TreeModelColumn<pid_t> ppid;
        Gtk::TreeModelColumn<int> pri;
        Gtk::TreeModelColumn<int> ni;
        Gtk::TreeModelColumn<Glib::ustring> state;

        proccols() { add(name); add(cmd); add(usage); add(pid); add(ppid); add(pri); add(ni); add(state); }
    } columns;

    std::unordered_map<pid_t, long> prev_times;
    Gtk::SortType curr_sort_type = Gtk::SortType::ASCENDING;
    void column_clicked(int column_index);
public:
    proc_list_conf(Gtk::TreeView& proc_list);
    void update_list();
};

#endif