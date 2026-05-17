#include <array>
#include <cstdio>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

/**
 * References: 
 *   https://stackoverflow.com/questions/67273/how-do-you-iterate-through-every-file-directory-recursively-in-standard-c
 *   https://en.cppreference.com/cpp/filesystem/path/operator_slash?utm_source=chatgpt.com
 * 
 * @param target_name wanted information (amdgpu, k10temp (CPU), nvme).
 * @returns the directory where target_info is located.
 */
fs::path hwmon_iter(std::string target_name)
{
    std::string path = "/sys/class/hwmon";
    
    for (const auto& entry : fs::directory_iterator(path))
    {
        fs::path name_file = entry.path() / "name";

        std::ifstream file(name_file);
        std::string name;
        file >> name;

        file.close();

        if (name == target_name)
        {
            return entry.path();
        }
    }

    return fs::path(); // empty path, not found
}

/**
 * Source - https://stackoverflow.com/a/478960
 * Posted by waqas, modified by community. See post 'Timeline' for change history
 * Retrieved 2026-04-28, License - CC BY-SA 4.0
 * 
 * @returns String output of executed command. Used to extract name of GPU.
 */
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, void(*)(FILE*)> pipe(
        popen(cmd, "r"),
        [](FILE* f) {
            std::ignore = pclose(f);
        }
    );

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
