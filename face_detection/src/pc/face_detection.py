import cv2 as cv  # Please install with PIP: pip install cv2
import numpy as np
import urllib.request
import serial

# pip install pyserial
CAM_URL ='http://192.168.43.13/capture?'
ARDUINO_PORT = 'COM7'

face_cascade = cv.CascadeClassifier("./pretrain_model/haarcascade_frontalface_default.xml")

LEFT = '4'
RIGHT = '3'
UP = '1'
DOWN = '2'

serialPort = serial.Serial(port=ARDUINO_PORT, baudrate=10000, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)


def movement(x, y):
    x_mid, y_mid = 120, 130

    if (x > x_mid-20) and (x < x_mid + 20):
        lr = None
    else:
        lr = RIGHT if x < x_mid else LEFT

    if (y > y_mid-20) and (y < y_mid + 20):
        upd = None
    else:
        upd = DOWN if y < y_mid else UP

    return lr, upd


def face_detection(img):
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 2)
    # Draw rectangle around the faces

    for (x, y, w, h) in faces:
        cv.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 1)

        lr, upd = movement(x, y)
        return img, lr, upd

    return img, None, None


def send_command(cmd):
    serialPort.write(cmd.encode('ascii'))


def cam():
    lr_lst = []
    upd_lst = []

    while True:

        imgResponse = urllib.request.urlopen(CAM_URL)
        imgNp = np.array(bytearray(imgResponse.read()), dtype=np.uint8)
        frame = cv.imdecode(imgNp, -1)

        frame, lr, upd = face_detection(frame)

        if lr is not None:
            lr_lst.append(lr)
        if upd is not None:
            upd_lst.append(upd)

        if len(lr_lst+upd_lst) > 1:
            cmd = ''.join(lr_lst+upd_lst)
            send_command(cmd)
            lr_lst, upd_lst = [], []

        cv.imshow('Window', frame)
        key = cv.waitKey(100)

        if key == (ord('q')):
            break

    cv.destroyAllWindows()


if __name__ == '__main__':
    cam()
