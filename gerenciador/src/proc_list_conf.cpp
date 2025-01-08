#include <proc_list_conf.hpp>

proc_list_conf::proc_list_conf(Gtk::TreeView& proc_list) {
    list_store = Gtk::ListStore::create(columns);
    proc_list.set_model(list_store);

    proc_list.append_column("Nome", columns.name);
    proc_list.append_column_numeric("\%CPU", columns.usage, "%.2f");
    proc_list.append_column("PID", columns.pid);
    proc_list.append_column("PPID", columns.ppid);
    proc_list.append_column("PRI", columns.pri);
    proc_list.append_column("STAT", columns.status);

    for (guint i = 0; i < proc_list.get_n_columns(); i++) {
        Gtk::TreeViewColumn* col = proc_list.get_column(i);
        col->set_reorderable();
        col->set_resizable();
        col->set_expand();
    }

    auto row = *(list_store->append());
    row[columns.name] = "test";
    row[columns.pid] = 1010;
    row[columns.ppid] = 10;
    row[columns.pri] = 2;
    row[columns.status] = "R";
    row[columns.usage] = 0.4;
    
    for (int i = 0; i < 30; i++) {
    row = *(list_store->append());
    row[columns.name] = "test2";
    row[columns.pid] = 2020;
    row[columns.ppid] = 11;
    row[columns.pri] = 3;
    row[columns.status] = "A";
    row[columns.usage] = 0.61;
    }

}
