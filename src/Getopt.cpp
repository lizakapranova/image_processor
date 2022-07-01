#include "../includes/Getopt.h"

ParsedInput Parse(int argc, char **argv) {
    ParsedInput parsed_input;
    if (argc == 1) {
        std::string info = "It is an app with graphic filters for your BMP image"
                           "These are filters and parameters that you can use:"
                           "-crop width height : crop"
                           "-gs : grayscale"
                           "-neg : negative"
                           "-sharp : sharpening"
                           "-edge threshold : edge detection"
                           "-blur sigma : Gaussian Blur";
        for (const auto &str: info) {
            std::cout << str << std::endl;
        }
        return parsed_input;
    }
    parsed_input.input_file = argv[1];
    try {
        if (argc > 2) {
            parsed_input.output_file = argv[2];
        } else {
            throw argc;
        }
    }
    catch (int i) {
        std::cout << "No output file" << std::endl;
        return {};
    }
    if (argc > 3) {
        parsed_input.filters_and_params = GetOpt(argc, argv);
    }

    return parsed_input;
}

std::vector<Filters> GetOpt(int argc, char **argv) {
    std::vector<Filters> filters;
    for (int i = 3; i < argc; ++i) {
        std::string command(argv[i]);
        if (command == "-crop") {
            std::string width_str(argv[i + 1]);
            std::string height_str(argv[i + 2]);
            try {
                double width = std::stod(width_str);
                double height = std::stod(height_str);
                Filters filter{command, {width, height}};
                filters.push_back(filter);
                i += 2;
            }
            catch (std::exception()) {
                std::cout << "Incorrect parameters" << std::endl;
                return {};
            }
        } else if (command == "-gs" || command == "-neg" || command == "-sharp") {
            Filters filter{command};
            filters.push_back(filter);
        } else if (command == "-edge") {
            std::string threshold_str = (argv[i + 1]);
            try {
                double threshold = std::stod(threshold_str);
                Filters filter{command, {threshold}};
                filters.push_back(filter);
                ++i;
            } catch (std::exception()) {
                std::cout << "Incorrect parameters" << std::endl;
                return {};
            }
        } else if (command == "-blur") {
            std::string sigma_str = (argv[i + 1]);
            try {
                double sigma = std::stod(sigma_str);
                Filters filter{command, {sigma}};
                filters.push_back(filter);
                ++i;
            } catch (std::exception()) {
                std::cout << "Incorrect parameters" << std::endl;
                return {};
            }
        } else {
            throw std::invalid_argument("Incorrect command");
        }
    }
    return filters;
}