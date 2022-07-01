#pragma once

#include "Image.h"

#include <exception>
#include <fstream>
#include <string>
#include <vector>

#pragma pack(push, 1)

struct BMPHeader {
    uint16_t file_type{0};
    uint32_t file_size{0};
    uint16_t reserved_1{0};
    uint16_t reserved_2{0};
    uint32_t offset{0};
};

struct DIBHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};

    uint16_t planes{1};
    uint16_t bit_count{0};
    uint32_t compression{0};
    uint32_t size_image{0};

    int32_t x_pixels_pm{0};
    int32_t y_pixels_pm{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};

#pragma pack(pop)

class BMPReader {
public:
    explicit BMPReader(const std::string &input_file);

    void Read();

    void Close();

    Image Data();

private:
    std::ifstream file_;
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    std::vector<std::vector<Pixel>> data_;
};
