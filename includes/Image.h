#pragma once

#include <vector>

struct Pixel {
    double red;
    double green;
    double blue;
};

struct Image {
    Image(std::vector<std::vector<Pixel>> &data);

    size_t GetWidth() const;

    size_t GetHeight() const;

    void SetWidth(size_t new_width);

    void SetHeight(size_t new_height);

    std::vector<std::vector<Pixel>> picture;
private:
    size_t width_;
    size_t height_;

};

