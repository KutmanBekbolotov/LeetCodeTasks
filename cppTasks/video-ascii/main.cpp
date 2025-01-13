#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

const std::string ASCII_CHARS = " .:-=+*#%@";

char mapToAscii(int pixelValue) {
    int numChars = ASCII_CHARS.size();
    return ASCII_CHARS[pixelValue * (numChars - 1) / 255];
}

std::string frameToAscii(const cv::Mat& frame, int outputWidth) {
    int outputHeight = frame.rows * outputWidth / frame.cols / 2;
    cv::Mat resized, gray;

    cv::resize(frame, resized, cv::Size(outputWidth, outputHeight));
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

    std::string asciiArt;
    for (int i = 0; i < gray.rows; ++i) {
        for (int j = 0; j < gray.cols; ++j) {
            int pixelValue = gray.at<uchar>(i, j);
            asciiArt += mapToAscii(pixelValue);
        }
        asciiArt += '\n';
    }

    return asciiArt;
}

void playAsciiVideo(const std::string& videoPath, int outputWidth, int fps = 30) {
    cv::VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video file!" << std::endl;
        return;
    }

    cv::Mat frame;
    int frameCount = 0;
    while (cap.read(frame)) {
        std::cout << "Processing frame: " << ++frameCount << std::endl;  // Выводим информацию о кадре
        std::string asciiFrame = frameToAscii(frame, outputWidth);
        std::cout << "\033[H\033[J" << asciiFrame; // Очистка консоли
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }

    cap.release();
}


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <video_path> [output_width]" << std::endl;
        return -1;
    }

    std::string videoPath = argv[1];
    int outputWidth = argc > 2 ? std::stoi(argv[2]) : 80;

    playAsciiVideo(videoPath, outputWidth);
    return 0;
}
