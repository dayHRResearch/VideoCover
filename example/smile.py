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

import cv2


parser = argparse.ArgumentParser('Extract video key frame and extract smiley face feature')

parser.add_argument('--input_dir', required=False, type=str, default='./video',
                    help='Enter the key frame saved directory in video.')
parser.add_argument('--output_dir', required=False, tyep=str, default='./smile.png')

args = parser.parse_args()

if not os.path.exists(args.output_dir):
    os.makedirs(args.output_dir)

#
facePath = "../data/face.xml"
faceCascade = cv2.CascadeClassifier(facePath)

# 笑脸检测器
smilePath = "../data/smile.xml"
smileCascade = cv2.CascadeClassifier(smilePath)


def main():
    for file in os.listdir(args.input_dir):
        file_path = os.path.join(args.input_dir, file)
        img = cv2.imread(file_path)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # First, it detects the face and returns a rectangle that holds the face
        faces = faceCascade.detectMultiScale(
            gray,
            scaleFactor=1.1,
            minNeighbors=8,
            minSize=(55, 55),
            flags=cv2.CASCADE_SCALE_IMAGE
        )

        # Draw each face and extract the area of the face
        for (x, y, w, h) in faces:
            cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 2)
            roi_gray = gray[y:y + h, x:x + w]
            roi_color = img[y:y + h, x:x + w]

            # Smiley face detection
            smile = smileCascade.detectMultiScale(
                roi_gray,
                scaleFactor=1.16,
                minNeighbors=30,
                minSize=(15, 15),
                flags=cv2.CASCADE_SCALE_IMAGE
            )

            # Frame the corners of the mouth and label the smiling face.
            for (x2, y2, w2, h2) in smile:
                cv2.rectangle(
                    roi_color, (x2, y2), (x2 + w2, y2 + h2), (255, 0, 0), 2)
                cv2.putText(img, 'Smile', (x, y - 7), 3,
                            1.2, (0, 255, 0), 2, cv2.LINE_AA)

            if smile is None:
                continue
            else:
                cv2.imwrite("../example/smile.png", img)


if __name__ == '__main__':
    main()
