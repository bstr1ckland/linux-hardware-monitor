#include <filesystem>
#include <fstream>

/**
 * @returns total amount of GB of ram in system.
 */
double get_total_ram()
{
    std::ifstream file("/proc/meminfo");
    std::string line;

    while (getline(file, line))
    {
        if (line.find("MemTotal") != std::string::npos)
        {
            size_t value = line.find_first_of("0123456789");
            unsigned long long kb = std::stoull(line.substr(value));
            return static_cast<double>(kb) / (1024.0 * 1024.0);
        }
    }

    file.close();

    return -1;
}

/**
 * @returns current amount of GB of ram in use.
 */
double get_used_ram()
{
    std::ifstream file("/proc/meminfo");
    std::string line;
    unsigned long long mem_total = 0, mem_available = 0;

    while (std::getline(file, line))
    {
        if (line.find("MemTotal:") != std::string::npos)
        {
            size_t pos = line.find_first_of("0123456789");
            mem_total = std::stoull(line.substr(pos));
        }
        else if (line.find("MemAvailable:") != std::string::npos)
        {
            size_t pos = line.find_first_of("0123456789");
            mem_available = std::stoull(line.substr(pos));
        }

        if (mem_total && mem_available)
            break;
    }

    if (mem_total == 0)
        return -1;

    return static_cast<double>(mem_total - mem_available) / (1024.0 * 1024.0);
}