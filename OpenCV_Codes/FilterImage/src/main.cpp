#include "Filter/image_filters.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[]) {
    auto filter_image = std::make_shared<ImageFilters>();

    if (argc < 2) {
        std::cerr << "Informe uma imagem!\n";
        std::exit(EXIT_FAILURE);
    }

    std::string title_original = "Imagem Original";
    std::string title_mask = "Filtro Aplicado";

    Mat image = imread(argv[1], IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Não foi possível ler a imagem\n";
        std::exit(EXIT_FAILURE);
    }
    imshow("Original", image);
    filter_image->applyFilter(title_mask, image, filter_image->robertsFilter);
    waitKey();

    return EXIT_SUCCESS;
}
