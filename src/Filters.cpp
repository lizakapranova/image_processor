#include "../includes/Filters.h"

#include <cmath>

Pixel IConvFilter::Convolution(size_t &height, size_t &width, std::vector<std::vector<Pixel>> &image) const {
    auto kernel = GetKernel();
    double red = 0;
    double green = 0;
    double blue = 0;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            Pixel pixel{0, 0, 0};
            if (!(height + i - 1 == -1 || width + i - 1 == -1 || height + i - 1 == image.size() ||
                  width + i - 1 == image[0].size())) {
                pixel = image[height + i - 1][width + i - 1];
            }
            red += pixel.red * kernel[i][j];
            green += pixel.green * kernel[i][j];
            blue += pixel.blue * kernel[i][j];
        }
    }
    red = std::min(1.0, std::max(0.0, red));
    green = std::min(1.0, std::max(0.0, green));
    blue = std::min(1.0, std::max(0.0, blue));

    return {red, green, blue};
}

void IColorFilter::Apply(Image &image) const {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.picture[i][j] = NewColorPixel(image.picture[i][j]);
        }
    }
}

Pixel NegativeFilter::NewColorPixel(Pixel pixel) const {
    double new_red = 1 - pixel.red;
    double new_green = 1 - pixel.green;
    double new_blue = 1 - pixel.blue;
    return {new_red, new_green, new_blue};
}

Pixel GrayscaleFilter::NewColorPixel(Pixel pixel) const {
    double pixel_color = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
    return {pixel_color, pixel_color, pixel_color};
}

std::vector<std::vector<double>> EdgeSegmentationFilter::GetKernel() const {
    std::vector<std::vector<double>> edge_matrix = {{0,  -1, 0},
                                                    {-1, 4,  -1},
                                                    {0,  -1, 0}};
    return edge_matrix;
}

void EdgeSegmentationFilter::Apply(Image &image) const {
    std::vector<std::vector<double>> kernel = GetKernel();
    std::vector<std::vector<Pixel>> image_picture_copy = image.picture;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel result_pixel = Convolution(i, j, image_picture_copy);
            if (result_pixel.red > threshold_) {
                result_pixel = {1, 1, 1};
            } else {
                result_pixel = {0, 0, 0};
            }
            image.picture[i][j] = result_pixel;
        }
    }
}

void GaussBlurFilter::Apply(Image &image) const {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            double red = 0;
            double green = 0;
            double blue = 0;
            for (size_t k = std::max(0, int(i - 2 * sigma_));
                 k < std::min(int(i + 3 * sigma_), int(image.GetHeight())); ++k) {
                for (size_t l = std::max(0, int(j - 2 * sigma_));
                     l < std::min(int(j + 3 * sigma_), int(image.GetWidth())); ++l) {
                    double constant =
                            (1 / (2 * M_PI * powl(sigma_, 2))) * exp(-(powl(std::max(i, k) - std::min(i, k), 2) +
                                                                       powl(std::max(j, l) - std::min(j, l), 2)) /
                                                                     (2 * powl(sigma_, 2)));
                    red += double(image.picture[k][l].red) * constant;
                    green += double(image.picture[k][l].green) * constant;
                    blue += double(image.picture[k][l].blue) * constant;
                }
            }
            image.picture[i][j] = {red, green, blue};
        }
    }
}

std::vector<std::vector<double>> GaussBlurFilter::GetKernel() const { return std::vector<std::vector<double>>(); }

std::vector<std::vector<double>> SharpeningFilter::GetKernel() const {
    std::vector<std::vector<double>> sharp_matrix = {{0,  -1, 0},
                                                     {-1, 5,  -1},
                                                     {0,  -1, 0}};
    return sharp_matrix;
}

void SharpeningFilter::Apply(Image &image) const {
    std::vector<std::vector<double>> kernel = GetKernel();
    std::vector<std::vector<Pixel>> image_picture_copy = image.picture;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.picture[i][j] = Convolution(i, j, image_picture_copy);
        }
    }
}

void CropFilter::Apply(Image &image) const {
    if (height_ < image.GetHeight()) {
        image.SetHeight(height_);
    }
    if (width_ < image.GetWidth()) {
        image.SetWidth(width_);
    }
}
