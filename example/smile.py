# Copyright 2019 DayHR Authors. All Rights Reserved.
# Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================


import os
import argparse
import time

import cv2


parser = argparse.ArgumentParser('Extract mp4 key frame and extract smile face feature!')

parser.add_argument('--video_path', required=False, type=str, default='./video1.mp4')
parser.add_argument('--images_dir', required=False, type=str, default='./video1',
                    help='Enter the key frame saved directory.')
parser.add_argument('--output_dir', required=False, type=str, default='./smile')

args = parser.parse_args()

# Create a directory if the file directory does not exist.
if not os.path.exists(args.images_dir):
    os.makedirs(args.images_dir)
if not os.path.exists(args.output_dir):
    os.makedirs(args.output_dir)

smile_path = args.output_dir + '/' + args.images_dir + '_smile.png'

# Face detector
facePath = '../data/face_improved.xml'
faceCascade = cv2.CascadeClassifier(facePath)

# Smile detector
smilePath = '../data/smile.xml'
smileCascade = cv2.CascadeClassifier(smilePath)


def video_to_image():
    """ The program runs the main function interface.
    """
    camera = cv2.VideoCapture(args.video_path)

    for i in range(0, 6000):
        res, image = camera.read()

        if not res:
            break

        if i % 17 == 0:
            cv2.imwrite(args.images_dir + '/' + str(i) + '.png', image)

    camera.release()


def detector_face():
    for file in os.listdir(args.images_dir):
        # Determine the user's maximum smile
        smile_degree_min = 0
        # file abs path
        file_path = os.path.join(args.images_dir, file)
        img = cv2.imread(file_path)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # First, it detects the face and returns a rectangle that holds the
        # face
        faces = faceCascade.detectMultiScale(
            gray,
            scaleFactor=1.1,
            minNeighbors=8,
            minSize=(55, 55),
            flags=cv2.CASCADE_SCALE_IMAGE
        )

        if faces is not None:
            # Draw each face and extract the area of the face
            for (x, y, w, h) in faces:
                # cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 2)
                face_image = gray[y:y + h, x:x + w]
                # roi_color = img[y:y + h, x:x + w]

                # Smiley face detection
                smile = smileCascade.detectMultiScale(
                    face_image,
                    scaleFactor=1.16,
                    minNeighbors=35,
                    minSize=(25, 25),
                    flags=cv2.CASCADE_SCALE_IMAGE
                )

                # Frame the corners of the mouth and label the smiling face.
                # for (x2, y2, w2, h2) in smile:
                #     cv2.rectangle(roi_color, (x2, y2), (x2 + w2, y2 + h2), (255, 0, 0), 2)
                #     cv2.putText(img, 'Smile', (x, y - 7), 3,1.2, (0, 255, 0), 2, cv2.LINE_AA)

                if smile is not None:
                    for i in smile:
                        smile_degree_max = i[3]
                        if smile_degree_max > smile_degree_min:
                            cv2.imwrite(smile_path, img)
                            smile_degree_min = smile_degree_max
                        else:
                            pass
        else:
            pass


if __name__ == '__main__':
    print(f'source video path: `{args.video_path}`.')
    print(f'target images dir: `{args.images_dir}`.')
    start = time.time()
    video_to_image()
    detector_face()
    print(f'Done! Times: {time.time() - start:.4f} s.')
