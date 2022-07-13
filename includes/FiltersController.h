#pragma once

#include "Image.h"
#include "Filters.h"

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

struct Filters {
    std::string filter;
    std::vector<double> params;
    int code;
};

enum Filters_codes {
    gray_scale,
    negative,
    sharpening,
    edge_segmentation,
    gaussian_blur,
    crop
};

class FiltersController {
public:
    explicit FiltersController(std::vector<Filters> filters_and_params) : filters_and_params_(std::move(
            filters_and_params)) {};

    void Apply(Image &image);

private:
    std::vector<Filters> filters_and_params_;
};

struct FilterMaker {
    explicit FilterMaker(Filters filter) : filter_(std::move(filter)) {};

    IFilter *MakeFilter();

    Filters filter_;
};