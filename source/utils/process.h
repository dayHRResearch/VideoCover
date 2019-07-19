#ifndef UTILS_PROCESS_H
#define UTILS_PROCESS_H
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/opencv.hpp"

#ifndef IO
#define IO
#include <iostream>
#endif  // IO

using namespace std;
using namespace cv;

// Divide video file into several consecutive frames.
int video_to_image() {
  VideoCapture capture;
  Mat frame;

  int fps_beak = 0;
  string videoName = "./video.mp4";

  frame = capture.open(videoName);
  if (!capture.isOpened()) return -1;

  // get all frame.
  long TotalVideoFrame = capture.get(CAP_PROP_FRAME_COUNT);
  // set start frame.
  long start = 1;
  // set end frame.
  long currentFrame = start;
  // set skip frame value.
  unsigned fpsBreak = 20;

  // Define a variable to control the end of the read video loop.
  bool flag = false;
  while (!flag) {
    // read next frame.
    if (!capture.read(frame)) {
      flag = true;
      return -1;
    };
    // Variables that control the specified frame.
    // Modify the value of the skip frame
    if (currentFrame % fpsBreak == 0) {
      string imagePath = "./images/" + to_string(currentFrame) + ".png";
      imwrite(imagePath, frame);
    }
    currentFrame++;

    if (currentFrame > TotalVideoFrame) flag = true;
  }
  capture.release();
  return 0;
}
#endif  // UTILS_PROCESS_H