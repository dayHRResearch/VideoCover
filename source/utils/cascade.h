#ifndef CASCADE_H
#define CASCADE_H
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/objdetect.hpp"

#ifndef IO
#define IO
#include <iostream>
#endif  // IO

using namespace std;
using namespace cv;

string cascadeName() {
  string faceCascadeName = samples::findFile("../data/face_improved.xml");
  string smileCascadeName = samples::findFile("../data/smile.xml");

  // if (!faceCascade.load(faceCascadeName)) {
  //   perror("ERROR: Could not load face cascade!\n");
  //   return false;
  // }

  // if (!smileCascade.load(smileCascadeName)) {
  //   perror("ERROR: Could not load smile cascade!\n");
  //   return -1;
  // }
  return faceCascadeName, smileCascadeName;
}

#endif  // CASCADE_H