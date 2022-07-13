#include "includes/BMPReader.h"
#include "includes/BMPWriter.h"
#include "includes/FiltersController.h"
#include "includes/Getopt.h"
#include "includes/Image.h"

int main(int argc, char **argv) {
    const ParsedInput parsed_line = Parse(argc, argv);
    BMPReader bmp_input(parsed_line.input_file);
    bmp_input.Read();
    bmp_input.Close();
    Image image = bmp_input.Data();

    FiltersController filters_controller(parsed_line.filters_and_params);
    filters_controller.Apply(image);

    BMPWriter bmp_output(parsed_line.output_file);
    bmp_output.Write(image);
    bmp_output.Close();
    return 0;
}
