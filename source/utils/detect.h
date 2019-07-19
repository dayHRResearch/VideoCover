#ifndef UTILS_DETECT_H
#define UTILS_DETECT_H
#include "opencv4/opencv2/core/core.hpp"
#include "opencv4/opencv2/opencv.hpp"

#ifndef IO
#define IO
#include <iostream>
#endif  // IO

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif  // VECTOR

using namespace std;
using namespace cv;

vector<Rect> detectFaces(Mat gray) {
  CascadeClassifier facesCascade;
  vector<Rect> faces;
  facesCascade.load("../data/face.xml");
  facesCascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE,
                                Size(30, 30));
  return faces;
}

vector<Rect> detectSmile(Mat faces) {
  CascadeClassifier smileCascade;
  vector<Rect> smiles;
  smileCascade.load("../data/smile.xml");
  smileCascade.detectMultiScale(faces, smiles, 1.1, 2, 0 | CASCADE_SCALE_IMAGE,
                                Size(30, 30));
  return smiles;
}

void detectDrawEyes(Mat img, Mat img_gray) {
  vector<Rect> faces = detectFaces(img_gray);
  for (size_t i = 0; i < faces.size(); i++) {
    Mat faceROI = img_gray(faces[i]);
    CascadeClassifier eyes_cascade;
    eyes_cascade.load("../data/eye.xml");
    vector<Rect> eyes;
    eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2,
                                  0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    for (size_t j = 0; j < eyes.size(); j++) {
      Point eyes_center(faces[i].x + eyes[j].x + eyes[j].width / 2,
                        faces[i].y + eyes[j].y + eyes[j].height / 2);
      int r = cvRound((eyes[j].width + eyes[j].height) * 0.25);
      circle(img, eyes_center, r, Scalar(255, 0, 0), 1, 8, 0);
    }
  }
  namedWindow("detect and draw eyes");
  imshow("detect and draw eyes", img);
}

void saveFaces(Mat img, Mat img_gray) {
  vector<Rect> faces = detectFaces(img_gray);
  for (size_t i = 0; i < faces.size(); i++) {
    stringstream buffer;
    buffer << i;
    string saveName = "smile" + buffer.str() + ".png";
    Rect roi = faces[i];
    imwrite(saveName, img(roi));
  }
}
void drawFaces(Mat img, vector<Rect> faces) {
  namedWindow("draw faces");
  for (size_t i = 0; i < faces.size(); i++) {
    // 先确定人脸矩形中心坐标,再根据该坐标画椭圆
    Point center(faces[i].x + faces[i].width / 2,
                 faces[i].y + faces[i].height / 2);
    ellipse(img, center, Size(faces[i].width / 2, faces[i].height / 1.5), 0, 0,
            360, Scalar(0, 255, 0), 2, 8, 0);
  }
  imshow("draw faces", img);
}

#endif  // UTILS_DETECT_H