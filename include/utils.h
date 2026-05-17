#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string hwmon_iter(std::string target_info);
std::string exec(const char* cmd);

#endif // UTILS_H