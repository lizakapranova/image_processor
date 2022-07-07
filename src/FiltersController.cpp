#include "../includes/FiltersController.h"

void FiltersController::Apply(Image &image) {
    std::vector<IFilter *> filters;

    for (const auto &filter: filters_and_params_) {
        FilterMaker filter_maker(filter);
        filters.push_back(filter_maker.MakeFilter());
    }

    for (auto filter: filters) {
        filter->Apply(image);
        delete filter;
    }
}

IFilter *FilterMaker::MakeFilter() {
    if (filter_.filter == "-gs") {
        return new GrayscaleFilter;
    }
    if (filter_.filter == "-neg") {
        return new NegativeFilter;
    }
    if (filter_.filter == "-sharp") {
        return new SharpeningFilter;
    }
    if (filter_.filter == "-edge") {
        return new EdgeSegmentationFilter(filter_.params[0]);
    }
    if (filter_.filter == "-blur") {
        return new GaussBlurFilter(filter_.params[0]);
    }
    if (filter_.filter == "-crop") {
        return new CropFilter(filter_.params[0], filter_.params[1]);
    }
}
