#include <ctime>
#include <random>
#include <string>
#include <boost/filesystem.hpp>
#include "Helper.h"

int random_int() {
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    return 1000 + std::rand();
}

std::string random_file_path() {
    auto file_path = boost::filesystem::temp_directory_path();
    file_path += std::to_string(random_int());

    return file_path.string();
}
