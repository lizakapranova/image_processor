#pragma once

#include "FiltersController.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>


struct ParsedInput {
    std::string input_file;
    std::string output_file;
    std::vector<Filters> filters_and_params;
};

ParsedInput Parse(int argc, char **argv);

std::vector<Filters> GetOpt(int argc, char **argv);
