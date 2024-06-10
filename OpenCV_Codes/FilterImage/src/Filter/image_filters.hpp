#pragma once

#include <opencv2/opencv.hpp>

class ImageFilters {
    using Mat = cv::Mat;
    using MatDouble_ = cv::Mat_<double>;

  public:
    const Mat isolatedPointsFilter =
        (MatDouble_(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
    const Mat vertical_filter =
        (MatDouble_(3, 3) << -1, 2, -1, -1, 2, -1, -1, 2, -1);
    const Mat horizontal_filter =
        (MatDouble_(3, 3) << -1, -1, -1, 2, 2, 2, -1, -1, -1);
    const Mat diagonal_filter =
        (MatDouble_(3, 3) << 2, -1, -1, -1, 2, -1, -1, -1, 2);
    const Mat reverseDiagonal_filter =
        (MatDouble_(3, 3) << -1, -1, 2, -1, 2, -1, 2, -1, -1);
    const Mat robertsFilter = (MatDouble_(2, 2) << -1, 0, 0, 1);
    const Mat prewitt_filter =
        (MatDouble_(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
    const Mat sobel_filter = (MatDouble_(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

    void applyFilter(const std::string &title, Mat &image, const Mat &filter) {
        cv::namedWindow(title, cv::WINDOW_NORMAL);
        cv::resizeWindow(title, 600, 600);

        Mat result;
        cv::filter2D(image, result, -1, filter, cv::Point(-1, -1), 0,
                     cv::BORDER_DEFAULT);
        cv::imshow(title, result);
    }
};
