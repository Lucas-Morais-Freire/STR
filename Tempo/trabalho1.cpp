#include <iostream>
#include <time.h>
#include <unistd.h>
#include <string>

int main()
{
	struct tm *tm_ptr;  
	time_t curr_time;
    std::string output;
    int tz;

    std::cout << "Insira o fuso horario: GMT ";
    std::cin >> tz;
    if (tz < -12 || tz > 12) {
        std::cout << "Fuso horario invalido.\n";
        return -1;
    }

    while(true) {
        time(&curr_time);
        tm_ptr = gmtime(&curr_time);

        output = "Data: " + std::to_string(tm_ptr->tm_mday) + "/" + std::to_string(tm_ptr->tm_mon+1) + "/" + std::to_string(tm_ptr->tm_year+1900) + "\n" +
                 "Hora: " + std::to_string(tm_ptr->tm_hour + tz) + ":" + std::to_string(tm_ptr->tm_min) + ":" + std::to_string(tm_ptr->tm_sec) + "\n";
        std::cout << output;

        sleep(1);

        std::cout << "\033[1A\033[2K\033[1A\033[2K";
    }

    return 0;
}