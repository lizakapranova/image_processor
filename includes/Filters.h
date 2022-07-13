#pragma once

#include "Image.h"

#include <vector>
#include <cmath>

struct IFilter {
    virtual void Apply(Image &image) const = 0;

    virtual ~IFilter() = default;
};

struct IConvFilter : IFilter {
    IConvFilter() = default;

    virtual std::vector<std::vector<double>> GetKernel() const = 0;

protected:

    Pixel Convolution(size_t &height, size_t &width, std::vector<std::vector<Pixel>> &image) const;
};

struct IColorFilter : IFilter {
    void Apply(Image &image) const override;

protected:

    virtual Pixel NewColorPixel(Pixel pixel) const = 0;
};

struct EdgeSegmentationFilter : IConvFilter {
    explicit EdgeSegmentationFilter(const double &threshold) : threshold_(threshold) {};

    std::vector<std::vector<double>> GetKernel() const override;

    void Apply(Image &image) const override;

    double threshold_;
};

struct GaussBlurFilter : IConvFilter {
    explicit GaussBlurFilter(const double &sigma) : sigma_(sigma) {};

    void Apply(Image &image) const override;

    std::vector<std::vector<double>> GetKernel() const override;

    double sigma_;
};

struct SharpeningFilter : IConvFilter {
    std::vector<std::vector<double>> GetKernel() const override;

public:
    void Apply(Image &image) const override;
};

struct NegativeFilter : IColorFilter {
    Pixel NewColorPixel(Pixel pixel) const override;
};

struct GrayscaleFilter : IColorFilter {
    Pixel NewColorPixel(Pixel pixel) const override;
};

struct CropFilter : IFilter {
    CropFilter(int width, int height) : height_(height), width_(width) {};
    int height_;
    int width_;
public:
    void Apply(Image &image) const override;
};
