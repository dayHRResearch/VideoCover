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


import cv2
import os
# 要提取视频的文件名，隐藏后缀
sourceFileName = 'pikachu'
# 在这里把后缀接上
video_path = os.path.join("", "", sourceFileName + '.mp4')
times = 1
# 提取视频的频率，每25帧提取一个
frameFrequency = 1
# 输出图片到当前目录video文件夹下
outPutDirName = 'video/' + sourceFileName + '/'
if not os.path.exists(outPutDirName):
    # 如果文件目录不存在则创建目录
    os.makedirs(outPutDirName)
camera = cv2.VideoCapture(video_path)
while True:
    times += 1
    res, image = camera.read()
    if not res:
        print('not res , not image')
        break
    if times % frameFrequency == 0:
        cv2.imwrite(outPutDirName + str(times) + '.png', image)
        print(outPutDirName + str(times) + '.png')
print('Done')
camera.release()
