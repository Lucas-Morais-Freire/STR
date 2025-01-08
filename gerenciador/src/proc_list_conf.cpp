// std
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

// my headers
#include <proc_list_conf.hpp>
#include <utils.hpp>

proc_list_conf::proc_list_conf(Gtk::TreeView& proc_list) : proc_list(proc_list) {
    list_store = Gtk::ListStore::create(columns);
    proc_list.set_model(list_store);
    proc_list.set_expand();

    proc_list.append_column("Nome", columns.name);
    proc_list.append_column("Comando", columns.cmd);
    proc_list.append_column_numeric("\%CPU", columns.usage, "%.2f");
    proc_list.append_column("PID", columns.pid);
    proc_list.append_column("PPID", columns.ppid);
    proc_list.append_column("PRI", columns.pri);
    proc_list.append_column("NI", columns.ni);
    proc_list.append_column("STAT", columns.state);

    for (guint i = 0; i < proc_list.get_n_columns(); i++) {
        Gtk::TreeViewColumn* col = proc_list.get_column(i);
        col->set_reorderable();
        col->set_resizable();
        col->set_expand();
        // col->set_sort_column(col->get_sort_column_id());
    }
    
   // Signal connection for column click to handle sorting
    proc_list.get_column(0)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 0));
    proc_list.get_column(1)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 1));
    proc_list.get_column(2)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 2));
    proc_list.get_column(3)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 3));
    proc_list.get_column(4)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 4));
    proc_list.get_column(5)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 5));
    proc_list.get_column(6)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 6));
    proc_list.get_column(7)->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &proc_list_conf::column_clicked), 7));

    update_list();
}

void proc_list_conf::column_clicked(int column_index) {
    // Toggle sort direction for the clicked column
    switch (column_index) {
        case 0:
            list_store->set_sort_column(columns.name, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
        case 1:
            list_store->set_sort_column(columns.cmd, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
        case 2:
            list_store->set_sort_column(columns.usage, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
        case 3:
            list_store->set_sort_column(columns.pid, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
        case 4:
            list_store->set_sort_column(columns.ppid, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
        case 5:
            list_store->set_sort_column(columns.pri, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
        case 6:
            list_store->set_sort_column(columns.ni, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
        case 7:
            list_store->set_sort_column(columns.state, curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING);
            break;
    }
    curr_sort_type = curr_sort_type == Gtk::SortType::ASCENDING ? Gtk::SortType::DESCENDING : Gtk::SortType::ASCENDING;
}

namespace fs = std::filesystem;
void proc_list_conf::update_list()
{
    static const long clock_ticks = sysconf(_SC_CLK_TCK);
    // clear the list
    list_store->clear();

    // open and iterate over all directories in the /proc folder
    for (const auto& dir : fs::directory_iterator("/proc")) {
        // get the name of the directory
        std::string dirname = std::string(dir.path()).substr(6);
        // check if it is an unsigned integer (valid PID)
        if (utils::is_uint(dirname)) {
            // if it is, append a new empty row to the list store
            Gtk::TreeRow row = *(list_store->append());

            // open the stat file to get the PRI and NI values, alongside some values used in the cpu usage calculation.
            std::ifstream file(std::string(dir.path()) + "/stat", std::ios_base::in);
            if (!file.is_open()) {
                list_store->erase(std::prev(list_store->children().end()));
                continue;
            }

            std::string val;
            long utime = 0, stime = 0;
            for (int i = 0; i < 22; i++) {
                file >> val;
                if (i == 13) {
                    utime = std::stol(val);            // 14th value is the uptime by the CPU clock
                } else if (i == 14) {
                    stime = std::stol(val);            // 15th value is the start time by the CPU clock
                } else if (i == 18) {
                    row[columns.pri] = std::stoi(val); // 19th value is the PRI
                } else if (i == 19) {
                    row[columns.ni] = std::stoi(val);  // 20th value is the NI
                }
            }

            // get cpu usage
            // check if the previous user + kernel time has not already been registered.
            pid_t pid = std::stoul(dirname);
            row[columns.pid] = pid;
            if (prev_times.find(pid) == prev_times.end()) { // if it has not, insert it and put 0 on it.
                prev_times.insert({pid, 0});
            }

            // find difference between the current times and last times.
            row[columns.usage] = 100.0*(utime + stime - prev_times[pid])/static_cast<double>(clock_ticks);
            // register current time
            prev_times[pid] = utime + stime;
            file.close();

            // now, open the status file to get the other info
            file.open(std::string(dir.path()) + "/status", std::ios_base::in);
            if (!file.is_open()) {
                list_store->erase(std::prev(list_store->children().end()));
                continue;
            }

            // get Name, PPid and State
            std::stringstream stream;
            std::string line;
            while(std::getline(file, line)) {
                if (line.find("Name") == 0) {
                    stream.str(line);
                    stream.clear();
                    stream >> val >> val;
                    row[columns.name] = val;
                } else if (line.find("State") == 0) {
                    stream.str(line);
                    stream.clear();
                    stream >> val >> val;
                    row[columns.state] = val;
                } else if (line.find("PPid") == 0) {
                    stream.str(line);
                    stream.clear();
                    stream >> val >> val;
                    row[columns.ppid] = std::stoul(val);
                    break;
                }
            }


            file.close();
            // get cmdline
            file.open(std::string(dir.path()) + "/cmdline", std::ios_base::in);
            if (!file.is_open()) {
                list_store->erase(std::prev(list_store->children().end()));
                continue;
            }

            file >> val;
            row[columns.cmd] = val;

            file.close();
        }
    }
}
