#include "../include/process.h"

using namespace cv;

const char *forward_slash = "/";
const char *backward_slash = "\\";
const char *suffix_png = ".png";
const char *suffix_jpg = ".jpg";

/**
 * Divide video file into several consecutive frames.
 * Args:
 *   video_name: Name of video file
 *   dir_name: Video Cut into Picture Preserved Address
 * Returns:
 *   success return 0, else return -1
 * @ author: Changyu Liu
 * @ last modifly time: 2019.7.25
 */
int video_to_image(const char *video_name, const char *dir_name) {
  VideoCapture capture;
  Mat frame;

  int fps_beak = 0;

  frame = capture.open(video_name);
  if (!capture.isOpened()) return -1;

  // get all frame.
  long total_video_frame = capture.get(CAP_PROP_FRAME_COUNT);
  // set start frame.
  long start = 1;
  // set end frame.
  long current_frame = start;
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
    if (current_frame % fpsBreak == 0) {
      char *dir = strcat((char *)dir_name, forward_slash);
      char *file_name = strcat((char *)current_frame, suffix_png);
      char *img_path = strcat(dir, file_name);
      imwrite(img_path, frame);
    }
    current_frame++;

    if (current_frame > total_video_frame) flag = true;
  }
  capture.release();
  return 0;
}