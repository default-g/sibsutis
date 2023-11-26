import cv2
import os
import easyocr
import re


def split_video_into_frames(path: str):
    try:
        if not os.path.exists('images'):
            os.makedirs('images')
    except OSError:
        print('Error creating directory')

    cam = cv2.VideoCapture(path)
    currentFrame = 0

    while True:
        cam.set(cv2.CAP_PROP_POS_MSEC, currentFrame * 1000)
        ret, frame = cam.read()
        if not ret:
            return

        name = './images/frame' + str(currentFrame) + '.jpg'
        print('Creating %s' % name)
        cv2.imwrite(name, frame)

        currentFrame += 1


if __name__ == '__main__':
    split_video_into_frames('video.mp4')
    images_path = os.getcwd() + '/images/'
    images = os.listdir(images_path)
    plates = set()
    reader = easyocr.Reader(['ru'])
    for image_file in images:
        image_file = images_path + image_file
        image = cv2.imread(image_file)
        os.remove(image_file)
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        blur = cv2.GaussianBlur(gray, (5, 5), 0)
        edged = cv2.Canny(blur, 10, 200)
        contours, _ = cv2.findContours(edged, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        contours = sorted(contours, key=cv2.contourArea, reverse=True)
        approximations = []
        for c in contours:
            peri = cv2.arcLength(c, True)
            approx = cv2.approxPolyDP(c, 0.02 * peri, True)
            if len(approx) == 4:
                approximations.append(approx)
                break
        if len(approximations) == 0:
            continue
        pattern = re.compile(r"^[^+_=/*?@#$%&()'\"|â„;:{}.,`~<>}{][^\\]{1,20}$")
        for approx in approximations:
            (x, y, w, h) = cv2.boundingRect(approx)
            license_plate = gray[y:y + h, x:x + w]
            result = reader.readtext(license_plate)
            for detection in result:
                if detection[2] > 0.5:
                    license_plate_text = str(detection[1]).replace(' ', '').upper()
                    if pattern.match(license_plate_text):
                        print(license_plate_text)
                        plates.add(license_plate_text)
                        # text = f"{detection[0][1]} {detection[0][2] * 100:.2f}%"
                        text = str(license_plate_text)
                        cv2.putText(image, text, (x, y - 20), cv2.FONT_HERSHEY_COMPLEX, 0.75, (0, 255, 0), 2)
                        if not os.path.exists('detections'):
                            os.makedirs('detections')
                        cv2.imwrite(os.getcwd() + '/detections/' + str(license_plate_text) + '.jpg', image)
