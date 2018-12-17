#pragma once

#include <ctime>
#include <random>
#include <string>
#include <boost/filesystem.hpp>

// Generating a random number
int random_int();

// Generating a random temporary file path helping writing a test
std::string random_file_path();
