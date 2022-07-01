#pragma once

#include "BMPReader.h"
#include "Image.h"

#include <fstream>
#include <string>

class BMPWriter {
public:
    explicit BMPWriter(const std::string &output_file);

    void Write(const Image &image);

    void Close();

private:
    BMPHeader bmp_header_{.file_type = 19778, .offset = 54};
    DIBHeader dib_header_{.size = 40, .bit_count = 24};
    std::ofstream file_;
};