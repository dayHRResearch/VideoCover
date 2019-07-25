#include "./utils/detect.cc"
#include "./utils/dir.cc"
#include "./utils/download.cc"
#include "./utils/process.cc"

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
      "\tUsing OpenCV version 4.0.1");
  printf("\n");
}

// this func have `./utils/download.cc`
int download(const char *url, const char *save_path);

// this func have `./utils/dir.h`.
int check_dir_exists(const char *dir_name);
int clean_dir(const char *dir_name);

// this func has `./utils/process.h`
int video_to_image(const char *video_name, const char *dir_name);

// this func has `./utils/detect.h`
vector<Rect> detectSmile(Mat faces);

int main(int argc, const char *argv[]) {
  const char *url =
      "http://vodm2lzexwq.vod.126.net/vodm2lzexwq/"
      "4673d4ae-7078-42c1-affb-494b4ad0e687.mp4?resId="
      "254486990bfa2cd7aa860229db639341_1919639027_0&sign=i9VRqSZZJDUI%"
      "2B3hka7EpMg12silSgknLl2iTUoyqKT8%3D";
  const char *video_name = "video.mp4";
  const char *dir_name = "./video";
  download(url, video_name);

  if (!check_dir_exists(dir_name)) {
    perror("Warr: create dir error!\nreturn code -1.\n");
    return -1;
  }

  if (!video_to_image(video_name, dir_name)) {
    perror("Warr: video file conversion error!\nreturn code -1\n");
    return -1;
  }

  help();
  // Read the image, convert it into gray image, and then equalize the
  // histogram.
  const char *img_name = "./smile.png";
  const char *smile_name = "hh.png";
  Mat img = imread(img_name);
  if (img.empty()) {
    printf("No input images.\n");
    return -1;
  }
  Mat image_gray;
  cvtColor(img, image_gray, COLOR_BGR2GRAY);
  equalizeHist(image_gray, image_gray);

  vector<Rect> smiles = detectSmile(image_gray);

  if (!smiles.empty()) {
    imwrite(smile_name, img);
    return 0;
  } else {
    printf("No smile.\n");
    return -1;
  }

  if (clean_dir(dir_name)) {
    perror("Warr: delete dir success!\nreturn code -1\n");
    return -1;
  }

  return 0;
}