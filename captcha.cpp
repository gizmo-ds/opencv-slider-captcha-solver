#include "captcha.h"

using namespace cv;
using namespace std;

int captcha_slide(unsigned char *slide_data, int slide_data_len, unsigned char *bg_data, int bg_data_len) {
    std::vector<char> slideImg(slide_data, slide_data + slide_data_len);
    std::vector<char> bgImg(bg_data, bg_data + bg_data_len);
    Mat slide = cv::imdecode(cv::Mat(slideImg), cv::IMREAD_UNCHANGED);
    Mat bg = cv::imdecode(cv::Mat(bgImg), cv::IMREAD_UNCHANGED);
    if (slide.empty() || bg.empty()) {
        return -1;
    }

    cv::Rect roi(140, 490, 120, 120);
    cv::Mat _slide = slide(roi);

    std::vector<cv::Mat> channels;
    split(_slide, channels);
    if (channels.size() != 4) {
        return -2;
    }
    Mat mask = channels[3];
    threshold(mask, mask, 100, 255, cv::THRESH_BINARY);

    cvtColor(bg, bg, cv::COLOR_RGB2GRAY);
    GaussianBlur(bg, bg, cv::Size(3, 3), cv::BORDER_DEFAULT);

    Mat bgEdges;
    Canny(bg, bgEdges, 50, 200);

    cvtColor(_slide, _slide, cv::COLOR_RGB2GRAY);
    GaussianBlur(_slide, _slide, cv::Size(3, 3), cv::BORDER_DEFAULT);

    Mat slideEdges;
    Canny(_slide, slideEdges, 50, 200);

    Mat result;
    matchTemplate(bgEdges, slideEdges, result, cv::TM_CCOEFF_NORMED, mask);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    if (minVal > maxVal) maxLoc = minLoc;
    return maxLoc.x;
}
