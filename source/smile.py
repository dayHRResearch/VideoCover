import cv2
import os

# 人脸检测器
facePath = "./data/lbpcascade_frontalface.xml"
faceCascade = cv2.CascadeClassifier(facePath)

# 笑脸检测器
smilePath = "./data/haarcascade_smile.xml"
smileCascade = cv2.CascadeClassifier(smilePath)


def main():
    for file in os.listdir('../example/video/'):
        file_path = os.path.join('../example/video/', file)
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
                minNeighbors=35,
                minSize=(10, 10),
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
