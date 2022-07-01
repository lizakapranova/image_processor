#pragma once

#include "Image.h"
#include "Filters.h"

#include <vector>
#include <string>
#include <unordered_map>

struct Filters {
    std::string filter;
    std::vector<double> params;
};

class FiltersController {
public:
    explicit FiltersController(const std::vector<Filters> &filters_and_params) : filters_and_params_(
            filters_and_params) {};

    void Apply(Image &image);

private:
    std::vector<Filters> filters_and_params_;
};

struct FilterMaker {
    FilterMaker(const Filters& filter) : filter_(filter) {};
    IFilter* MakeFilter();

    Filters filter_;
};