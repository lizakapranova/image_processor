#include "../includes/BMPReader.h"

BMPReader::BMPReader(const std::string &input_file) {
    if (input_file.rfind(".bmp") == std::string::npos or input_file.rfind(".BMP") == std::string::npos) {
        file_.open(input_file, std::ios::binary | std::ios::in);
    } else {
        throw std::runtime_error("Wrong file type");
    }
    if (!file_.is_open()) {
        throw std::runtime_error("Unable to open input file");
    }
}

void BMPReader::Read() {
    file_.read(reinterpret_cast<char *>(&bmp_header_), sizeof(bmp_header_));
    file_.read(reinterpret_cast<char *>(&dib_header_), sizeof(dib_header_));
    
    int additional_size = 0;
    int full_width = dib_header_.width;

    if (dib_header_.width % 4 != 0) {
        additional_size = 4 - (dib_header_.width % 4);
        full_width += additional_size;
    }

    for (int i = 0; i < dib_header_.height; ++i) {
        std::vector<Pixel> row = {};
        for (int j = 0; j < full_width; ++j) {
            if (j >= dib_header_.width) {
                break;
            }
            Pixel pixel{0, 0, 0};
            unsigned char red;
            unsigned char green;
            unsigned char blue;
            file_.read(reinterpret_cast<char *>(&blue), 1);
            file_.read(reinterpret_cast<char *>(&green), 1);
            file_.read(reinterpret_cast<char *>(&red), 1);
            pixel.red = double(red / 255.0);
            pixel.green = double(green / 255.0);
            pixel.blue = double(blue / 255.0);
            row.push_back(pixel);
        }
        data_.push_back(row);
    }
}

void BMPReader::Close() {
    file_.close();
}

Image BMPReader::Data() {
    return {data_};
}
