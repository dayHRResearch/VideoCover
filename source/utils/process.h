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

  string videoName = "./video.mp4";

  frame = capture.open(videoName);
  if (!capture.isOpened()) return -1;

  namedWindow("output", WINDOW_AUTOSIZE);

  while (capture.read(frame)) {
    imshow("output", frame);
    waitKey(10);
  }
  capture.release();
  return 0;
}

// int images_to_video() {
//   VideoWriter writer;
//   IplImage *lpv_firstFrame =
//       cvLoadImage("D:\\intermittentObjectMotion\\sofa\\input\\in000001.jpg");
//   int liv_width = lpv_firstFrame->width;
//   int liv_height = lpv_firstFrame->height;
//   int liv_nChannels = lpv_firstFrame->nChannels;

//   // 初始化CvVideoWriter
//   CvVideoWriter *videoWriter =
//       writer.write("video.mp4",                    //写入视频的目录
//                    CV_FOURCC('X', 'V', 'I', 'D'),  //-1时弹出选择编码对话框
//                    25,                             //帧率
//                    cvSize(liv_width, liv_height), 1);

//   IplImage *lpv_imageFrame;
//   int i = 1;  //用于表示处于视频的多少帧
//   char imageDir
//       [70];  //略大于读入文件目录的总字符数，防止因为'\0'而出现栈溢出的情况
//   sprintf(imageDir, "D:\\intermittentObjectMotion\\sofa\\input\\in%06d.jpg",
//   i); while (lpv_imageFrame = cvLoadImage(imageDir)) {
//     cvShowImage("imageFrame", lpv_imageFrame);
//     cvWriteFrame(videoWriter, lpv_imageFrame);
//     i++;
//     sprintf(imageDir,
//     "D:\\intermittentObjectMotion\\sofa\\input\\in%06d.jpg",
//             i);  //读入视频目录
//     if (cvWaitKey(1) == 27) {
//       break;
//     }
//   }
//   cvReleaseVideoWriter(
//       &videoWriter);
//       //必须释放，否则会出现写好的视频丢失总帧数、不能快进的问题
// }
#endif  // UTILS_PROCESS_H