#include "../includes/Image.h"

#include <utility>

Image::Image(std::vector<std::vector<Pixel>> &data) {
    picture = std::move(data);
    width_ = picture[0].size();
    height_ = picture.size();
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

void Image::SetWidth(size_t new_width) {
    width_ = new_width;
}

void Image::SetHeight(size_t new_height) {
    height_ = new_height;
}