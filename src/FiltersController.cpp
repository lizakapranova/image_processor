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
    switch (filter_.code) {
        case gray_scale:
            return new GrayscaleFilter;
        case negative:
            return new NegativeFilter;
        case sharpening:
            return new SharpeningFilter;
        case edge_segmentation:
            return new EdgeSegmentationFilter(filter_.params[0]);
        case gaussian_blur:
            return new GaussBlurFilter(filter_.params[0]);
        case crop:
            return new CropFilter(int(filter_.params[0]), int(filter_.params[1]));
    }
    return {};
}
