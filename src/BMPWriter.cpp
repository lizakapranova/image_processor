#include "../includes/BMPWriter.h"

#include <iostream>

BMPWriter::BMPWriter(std::string const &output_file) {
    file_.open(output_file, std::ios_base::binary);
    if (!file_.is_open()) {
        throw std::runtime_error("Unable to open output file");
    }
}

void BMPWriter::Write(const Image &image) {
    dib_header_.height = image.GetHeight();
    dib_header_.width = image.GetWidth();
    dib_header_.size_image = dib_header_.height * dib_header_.width * 3;
    bmp_header_.file_size = dib_header_.size_image + bmp_header_.offset;

    file_.write(reinterpret_cast<char *>(&bmp_header_), sizeof(bmp_header_));
    file_.write(reinterpret_cast<char *>(&dib_header_), sizeof(dib_header_));

    int additional_size = 0;
    int full_width = dib_header_.width;

    if (dib_header_.width % 4 != 0) {
        additional_size = 4 - (dib_header_.width % 4);
        full_width += additional_size;
    }

    for (int i = 0; i < dib_header_.height; ++i) {
        for (int j = 0; j < full_width; ++j) {
            if (j >= dib_header_.width) {
                file_.write(nullptr, 1);
                file_.write(nullptr, 1);
                file_.write(nullptr, 1);
            } else {
                Pixel pixel = image.picture[i][j];
                unsigned char red = pixel.red * 255.0;
                unsigned char green = pixel.green * 255.0;
                unsigned char blue = pixel.blue * 255.0;
                file_.write(reinterpret_cast<char *>(&blue), 1);
                file_.write(reinterpret_cast<char *>(&green), 1);
                file_.write(reinterpret_cast<char *>(&red), 1);
            }
        }
    }
}

void BMPWriter::Close() {
    file_.close();
}
