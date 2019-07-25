#include "./utils/detect.cc"
#include "./utils/dir.cc"
#include "./utils/download.cc"
#include "./utils/process.cc"

using namespace std;
using namespace cv;

static void help() {
  cout << "\nThis program demonstrates the smile detector.Contains two "
          "functions:\n"
          "1.Converting Video Files to Pictures.\n"
          "2.Extract the smiling pictures from the pictures.\n"
          "Usage:\n"
          "./smile [--url=<the URL of the incoming video>]\n"
          "Example:\n"
          "./videocover "
          "http://vodm2lzexwq.vod.126.net/vodm2lzexwq/"
          "4673d4ae-7078-42c1-affb-494b4ad0e687.mp4?resId="
          "254486990bfa2cd7aa860229db639341_1919639027_0&sign=i9VRqSZZJDUI%"
          "2B3hka7EpMg12silSgknLl2iTUoyqKT8%3D";
  cout << endl;
  cout << "\tUsing OpenCV version 4.0.1";
  cout << endl;
  cout << endl;
  cout << endl;
}

// this func have `./utils/download.cc`
int download(const char *url, const char *save_path);

// this func have `./utils/dir.h`.
int __mkdir__(const char *dir_name);
int __rmdir__(const char *dir);

// this func has `./utils/process.h`
int video_to_image(const char *video_name, const char *dir_name);

// this func has `./utils/detect.h`
vector<Rect> detectSmile(Mat faces);

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    help();
    return 0;
  }
  const char *video_name = "video.mp4";
  const char *dir_name = "./video";
  string smile_name = "smile.png";
  if (download(argv[1], video_name) == -1) {
    perror("Warr: download video error!\nreturn code -1.\n");
    return -1;
  }
  printf("Download video done!\n");

  if (__mkdir__(dir_name) == -1) {
    perror("Warr: create dir error!\nreturn code -1.\n");
    return -1;
  }
  printf("Create dir done!\n");

  if (video_to_image(video_name, dir_name) == -1) {
    perror("Warr: video file conversion error!\nreturn code -1\n");
    return -1;
  }

  // Read the image, convert it into gray image, and then equalize the
  // histogram.
  for (int i = 1; i < 9999; i++) {
    string img_name = dir_name + forward_slash + to_string(i) + suffix_png;

    Mat img = imread(img_name);
    if (img.empty()) break;

    Mat image_gray;
    cvtColor(img, image_gray, COLOR_BGR2GRAY);
    equalizeHist(image_gray, image_gray);

    vector<Rect> smiles = detectSmile(image_gray);

    if (!smiles.empty()) imwrite(smile_name, img);
  }
  printf("Smile detector done!\n");

  if (__rmdir__(dir_name) == -1) {
    perror("Warr: delete temp dir error!\nreturn code -1\n");
    return -1;
  }
  printf("Delete dir done!\n");

  return 0;
}