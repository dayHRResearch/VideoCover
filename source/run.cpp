#include <iostream>
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/objdetect.hpp"

#include "./utils/detect.h"
#include "./utils/dir.h"
#include "./utils/process.h"

using namespace std;
using namespace cv;

static void help() {
  printf(
      "\nThis program demonstrates the smile detector.Contains two functions:\n"
      "1.Converting Video Files to Pictures.\n"
      "2.Extract the smiling pictures from the pictures.\n"
      "Usage:\n"
      "./smile [--url=<the URL of the incoming video>]\n"
      "Example:\n"
      "./smile 'https://www.google.com' \n"
      "\tUsing OpenCV version %s",
      CV_VERSION);
  printf("\n");
}

// this func have `./utils/dir.h`.
int checkDirExists();
int cleanDir();

// this func has `./utils/process.h`
int video_to_image();

// this func has `./utils/detect.h`
// vector<Rect> detectFaces(Mat gray);
vector<Rect> detectSmile(Mat faces);
// void detectDrawEyes(Mat img, Mat img_gray);
// void saveFaces(Mat img, Mat img_gray);
// void drawFaces(Mat img, vector<Rect> faces);

int main(int argc, const char** argv) {
  if (checkDirExists()) {
    perror("Warr: create dir error!\nreturn code -1.\n");
    return -1;
  }

  if (video_to_image()) {
    perror("Warr: video file conversion error!\nreturn code -1\n");
    return -1;
  }

  help();
  // Read the image, convert it into gray image, and then equalize the
  // histogram.
  string imageName = "./smile.png";
  string smileName = "./hahah.png";
  Mat img = imread(imageName);
  if (img.empty()) {
    printf("No input images.\n");
    return -1;
  }
  Mat image_gray;
  cvtColor(img, image_gray, COLOR_BGR2GRAY);
  equalizeHist(image_gray, image_gray);

  vector<Rect> smiles = detectSmile(image_gray);

  if (!smiles.empty()) {
    imwrite(smileName, img);
    return 0;
  } else {
    printf("No smile.\n");
    return -1;
  }

  if (cleanDir()) {
    perror("Warr: delete dir success!\nreturn code -1\n");
    return -1;
  }

  return 0;
}