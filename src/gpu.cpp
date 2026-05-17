#include <filesystem>
#include <fstream>
#include <string>
#include "utils.h"

using namespace std;
namespace fs = std::filesystem;

/**
 * Reference:
 *   https://stackoverflow.com/questions/23834624/remove-first-and-last-character-c
 *   https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
 * 
 * @returns Name of GPU model.
 */
std::string get_gpu_name()
{
    std::string name = exec("lspci -k | grep -EA2 'VGA|3D'");
    
    // get rid of trailing curly braces
    //name.erase(0, 1);
    //name.erase(name.size() - 1);

    return name;
}

/**
 * Reference:
 *   https://unix.stackexchange.com/questions/576707/how-to-monitor-amd-gpu-on-linux-server
 * 
 * @returns Temperature of GPU in degrees (C).
 */
double get_gpu_temp()
{
    fs::path path = hwmon_iter("amdgpu");
    std::ifstream file(path.string() + "/temp1_input");
    double temp;

    file >> temp;
    file.close();

    return temp;
}

/**
 * Reference:
 *   https://unix.stackexchange.com/questions/576707/how-to-monitor-amd-gpu-on-linux-server
 * 
 * @returns GPU Usage in percent.
 */
double get_gpu_usage()
{
    std::ifstream file("/sys/class/drm/card1/device/gpu_busy_percent");
    double usage;

    file >> usage;
    file.close();

    return usage;
}

// TODO: IMPLEMENT VRAM USAGE AND TOTAL