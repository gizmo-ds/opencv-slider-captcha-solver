#ifndef OPENCV_SLIDER_CAPTCHA_SOLVER_CAPTCHA_H
#define OPENCV_SLIDER_CAPTCHA_SOLVER_CAPTCHA_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#ifdef _WIN32
#define CAPTCHA_API __declspec(dllexport)
#else
#define CAPTCHA_API
#endif

extern "C" {
CAPTCHA_API int captcha_slide(unsigned char *slide_data, int slide_data_len, unsigned char *bg_data, int bg_data_len);
};

#endif //OPENCV_SLIDER_CAPTCHA_SOLVER_CAPTCHA_H
