/**
 * Copyright 2019 DayHR Authors. All Rights Reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ==============================================================================
 */

#include "../../include/process.h"

using namespace cv;
using namespace std;

const string forward_slash = "/";
const string backward_slash = "\\";
const string suffix_png = ".png";
const string suffix_jpg = ".jpg";

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
  int frame_cnt = 0;
  int num = 0;
  Mat img;

  VideoCapture cap(video_name);
  if (!cap.isOpened()) perror("Open video file failed!\n");

  bool flag = true;
  while (flag) {
    bool success = cap.read(img);
    if (img.empty()) flag = false;

    if (frame_cnt % 20 == 0) {
      ++num;
      string img_path = dir_name + forward_slash + to_string(num) + suffix_png;
      imwrite(img_path, img);
    }
    ++frame_cnt;
  }
  cap.release();
  return 0;
}